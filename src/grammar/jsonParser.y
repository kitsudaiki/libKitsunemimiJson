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
#include <jsonItems.hpp>

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

%type  <JsonItem*> json_abstract
%type  <JsonValue*> json_value
%type  <JsonArray*> json_array
%type  <JsonArray*> json_array_content
%type  <JsonObject*> json_object
%type  <JsonObject*> json_object_content

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
        $$ = (JsonItem*)$1;
    }
|
    json_array
    {
        $$ = (JsonItem*)$1;
    }
|
    json_value
    {
        $$ = (JsonItem*)$1;
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
        $$ = new JsonObject();
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
        $$ = new JsonObject();
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
        $$ = new JsonArray();
        $$->append($1);
    }

json_value:
    "identifier"
    {
        $$ = new JsonValue($1);
    }
|
    "number"
    {
        $$ = new JsonValue($1);
    }
|
    "float"
    {
        $$ = new JsonValue($1);
    }
|
    "string"
    {
        $$ = new JsonValue(driver.removeQuotes($1));
    }

%%

void Kitsune::Json::JsonParser::error(const Kitsune::Json::location& location,
                                      const std::string& message)
{
    driver.error(location, message);
}
