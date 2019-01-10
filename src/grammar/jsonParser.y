/**
 *  @file    jsonParser.y
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

%skeleton "lalr1.cc"

%defines

//requires 3.2 to avoid the creation of the stack.hh
%require "3.2"
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
;


%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%%
%start startpoint;


startpoint:
    "identifier"
    {
        //driver.setOutput($1);
    }

%%

void Kitsune::Json::JsonParser::error(const Kitsune::Json::location& location,
                                      const std::string& message)
{
    driver.error(location, message);
}
