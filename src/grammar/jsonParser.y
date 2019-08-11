%skeleton "lalr1.cc"

%defines
%require "3.0.4"

%define parser_class_name {JsonParser}

%define api.prefix {json}
%define api.namespace {Kitsune::Json}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include <iostream>
#include <data_structure/dataItems.hpp>

using Kitsune::Common::DataItem;
using Kitsune::Common::DataArray;
using Kitsune::Common::DataValue;
using Kitsune::Common::DataObject;


namespace Kitsune
{
namespace Json
{

class JsonParserInterface;

}  // namespace Json
}  // namespace Kitsune
}

// The parsing context.
%param { Kitsune::Json::JsonParserInterface& driver }

%locations

%code
{
#include <json_parsing/jsonParserInterface.hpp>
# undef YY_DECL
# define YY_DECL \
    Kitsune::Json::JsonParser::symbol_type jsonlex (Kitsune::Json::JsonParserInterface& driver)
YY_DECL;
}

// Token
%define api.token.prefix {Json_}
%token
    END  0  "end of file"
    EXPRESTART  "{"
    EXPREEND  "}"
    BRACKOPEN  "["
    BRACKCLOSE  "]"
    COMMA  ","
    ASSIGN  ":"
;


%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string"
%token <int> NUMBER "number"
%token <float> FLOAT "float"

%type  <DataItem*> json_abstract
%type  <DataValue*> json_value
%type  <DataArray*> json_array
%type  <DataArray*> json_array_content
%type  <DataObject*> json_object
%type  <DataObject*> json_object_content

%%
%start startpoint;


startpoint:
    json_object
    {
        driver.setOutput($1);
    }

json_abstract:
    json_object
    {
        $$ = (DataItem*)$1;
    }
|
    json_array
    {
        $$ = (DataItem*)$1;
    }
|
    json_value
    {
        $$ = (DataItem*)$1;
    }

json_object:
    "{" json_object_content "}"
    {
        $$ = $2;
    }

json_object_content:
    json_object_content "," "identifier" ":" json_abstract
    {
        $1->insert($3, $5);
        $$ = $1;
    }
|
    "identifier" ":" json_abstract
    {
        $$ = new DataObject();
        $$->insert($1, $3);
    }
|
    json_object_content "," "string" ":" json_abstract
    {
        $1->insert(driver.removeQuotes($3), $5);
        $$ = $1;
    }
|
    "string" ":" json_abstract
    {
        $$ = new DataObject();
        $$->insert(driver.removeQuotes($1), $3);
    }

json_array:
    "[" json_array_content "]"
    {
        $$ = $2;
    }

json_array_content:
    json_array_content "," json_abstract
    {
        $1->append($3);
        $$ = $1;
    }
|
    json_abstract
    {
        $$ = new DataArray();
        $$->append($1);
    }

json_value:
    "identifier"
    {
        $$ = new DataValue($1);
    }
|
    "number"
    {
        $$ = new DataValue($1);
    }
|
    "float"
    {
        $$ = new DataValue($1);
    }
|
    "string"
    {
        $$ = new DataValue(driver.removeQuotes($1));
    }

%%

void Kitsune::Json::JsonParser::error(const Kitsune::Json::location& location,
                                      const std::string& message)
{
    driver.error(location, message);
}
