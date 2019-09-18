/**
 *  @file    json_parser.y
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

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
#include <common_items/data_items.h>

using Kitsune::Common::DataItem;
using Kitsune::Common::DataArray;
using Kitsune::Common::DataValue;
using Kitsune::Common::DataMap;


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
#include <json_parsing/json_parser_interface.h>
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
    BOOL_TRUE  "true"
    BOOL_FALSE "false"
;


%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string"
%token <std::string> STRING_PLN "string_pln"
%token <int> NUMBER "number"
%token <float> FLOAT "float"

%type  <DataItem*> json_abstract
%type  <DataValue*> json_value
%type  <DataArray*> json_array
%type  <DataArray*> json_array_content
%type  <DataMap*> json_object
%type  <DataMap*> json_object_content

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
        $$ = new DataMap();
        $$->insert($1, $3);
    }
|
    json_object_content "," "string_pln" ":" json_abstract
    {
        $1->insert(driver.removeQuotes($3), $5);
        $$ = $1;
    }
|
    "string_pln" ":" json_abstract
    {
        $$ = new DataMap();
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
    "string_pln"
    {
        $$ = new DataValue($1);
    }
|
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
|
    "true"
    {
        $$ = new DataValue(true);
    }
|
    "false"
    {
        $$ = new DataValue(false);
    }

%%

void Kitsune::Json::JsonParser::error(const Kitsune::Json::location& location,
                                      const std::string& message)
{
    driver.error(location, message);
}
