%{ /* -*- C++ -*- */
/**
 *  @file    json_lexer.l
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
*/

# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <json_parsing/json_parser_interface.h>
# include <json_parser.h>

# undef yywrap
# define yywrap() 1


// The location of the current token.
# ifdef YY_DECL
# undef YY_DECL
# endif
# define YY_DECL \
    Kitsunemimi::Json::JsonParser::symbol_type jsonlex (Kitsunemimi::Json::JsonParserInterface& driver)
YY_DECL;
Kitsunemimi::Json::location jsonloc;

%}


%option noyywrap nounput batch debug yylineno prefix="json"

id    [a-zA-Z_0-9]*
long  -?([0-9]+)
blank [ \t]

%{
    # define YY_USER_ACTION  jsonloc.columns (yyleng);
%}

%%

%{
    jsonloc.step();
%}

{blank}+  jsonloc.step();
[\n]      {jsonloc.lines(1); jsonloc.step(); }
"{"       return Kitsunemimi::Json::JsonParser::make_EXPRESTART (jsonloc);
"}"       return Kitsunemimi::Json::JsonParser::make_EXPREEND (jsonloc);
"["       return Kitsunemimi::Json::JsonParser::make_BRACKOPEN (jsonloc);
"]"       return Kitsunemimi::Json::JsonParser::make_BRACKCLOSE (jsonloc);
","       return Kitsunemimi::Json::JsonParser::make_COMMA (jsonloc);
":"       return Kitsunemimi::Json::JsonParser::make_ASSIGN (jsonloc);

"true" return Kitsunemimi::Json::JsonParser::make_BOOL_TRUE (jsonloc);
"false" return Kitsunemimi::Json::JsonParser::make_BOOL_FALSE (jsonloc);
"null" return Kitsunemimi::Json::JsonParser::make_NULLVAL (jsonloc);

\"(\\.|[^"\\])*\" { return Kitsunemimi::Json::JsonParser::make_STRING(yytext, jsonloc); }

{long}      {
    errno = 0;
    long length = strtol(yytext, NULL, 10);
    if (!(LONG_MIN <= length
        && length <= LONG_MAX
        && errno != ERANGE))
    {
        driver.error(jsonloc, "integer is out of range");
    }
    return Kitsunemimi::Json::JsonParser::make_NUMBER (length, jsonloc);
}

{long}+"."{long}*	{
    double value = strtod( yytext , NULL );
    return Kitsunemimi::Json::JsonParser::make_FLOAT(value, jsonloc);
}

{id}       return Kitsunemimi::Json::JsonParser::make_IDENTIFIER(yytext, jsonloc);

[a-zA-Z_0-9|\-|.]* {
    return Kitsunemimi::Json::JsonParser::make_STRING_PLN(yytext, jsonloc);
}

.          driver.error(jsonloc, "invalid character");
<<EOF>>    return Kitsunemimi::Json::JsonParser::make_END(jsonloc);

%%


void Kitsunemimi::Json::JsonParserInterface::scan_begin(const std::string &inputString)
{
    Kitsunemimi::Json::location newJsonloc;
    jsonloc = newJsonloc;
    yy_flex_debug = m_traceParsing;
    yy_scan_string(inputString.c_str());
}

void Kitsunemimi::Json::JsonParserInterface::scan_end()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}


