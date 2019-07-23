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
#include <jsonItems.h>

namespace Kitsune
{
namespace Json
{

class JsonParserInterface;

}  // namespace Jinja2
}  // namespace Kitsune
}

// The parsing context.
%param { Kitsune::Json::JsonParserInterface& driver }

%locations

%code
{
#include <json_parsing/jsonParserInterface.h>
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

%type  <JsonItem> json_abstract
%type  <JsonItem> json_value
%type  <JsonItem> json_array
%type  <JsonItem> json_array_content
%type  <JsonItem> json_object
%type  <JsonItem> json_object_content

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
        $$ = $1;
    }
|
    json_array
    {
        $$ = $1;
    }
|
    json_value
    {
        $$ = $1;
    }

json_object:
    "{" json_object_content "}"
    {
        $$ = $2;
    }

json_object_content:
    json_object_content "," "identifier" ":" json_abstract
    {
        $1.insert($3, $5);
        $$ = $1;
    }
|
    "identifier" ":" json_abstract
    {
        $$ = JsonItem(JsonItem::OBJECT_TYPE);
        $$.insert($1, $3);
    }
|
    json_object_content "," "string" ":" json_abstract
    {
        $1.insert(driver.removeQuotes($3), $5);
        $$ = $1;
    }
|
    "string" ":" json_abstract
    {
        $$ = JsonItem(JsonItem::OBJECT_TYPE);
        $$.insert(driver.removeQuotes($1), $3);
    }

json_array:
    "[" json_array_content "]"
    {
        $$ = $2;
    }

json_array_content:
    json_array_content "," json_abstract
    {
        $1.append($3);
        $$ = $1;
    }
|
    json_abstract
    {
        $$ = JsonItem(JsonItem::ARRAY_TYPE);
        $$.append($1);
    }

json_value:
    "identifier"
    {
        $$ = JsonItem(std::string($1));
    }
|
    "number"
    {
        $$ = JsonItem($1);
    }
|
    "float"
    {
        $$ = JsonItem($1);
    }
|
    "string"
    {
        $$ = JsonItem(driver.removeQuotes($1));
    }

%%

void Kitsune::Json::JsonParser::error(const Kitsune::Json::location& location,
                                      const std::string& message)
{
    driver.error(location, message);
}
