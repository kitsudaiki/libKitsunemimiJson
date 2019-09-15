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
    Kitsune::Json::JsonParser::symbol_type jsonlex (Kitsune::Json::JsonParserInterface& driver)
YY_DECL;
Kitsune::Json::location jsonloc;

%}


%option noyywrap nounput batch debug yylineno prefix="json"

id    [a-zA-Z_0-9]*
int   -?([0-9]+)
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
"{"       return Kitsune::Json::JsonParser::make_EXPRESTART (jsonloc);
"}"       return Kitsune::Json::JsonParser::make_EXPREEND (jsonloc);
"["       return Kitsune::Json::JsonParser::make_BRACKOPEN (jsonloc);
"]"       return Kitsune::Json::JsonParser::make_BRACKCLOSE (jsonloc);
","       return Kitsune::Json::JsonParser::make_COMMA (jsonloc);
":"       return Kitsune::Json::JsonParser::make_ASSIGN (jsonloc);
\"(\\.|[^"\\])*\" { return Kitsune::Json::JsonParser::make_STRING(yytext, jsonloc); }


{int}      {
    errno = 0;
    long length = strtol(yytext, NULL, 10);
    if (!(INT_MIN <= length
        && length <= INT_MAX
        && errno != ERANGE))
    {
        driver.error(jsonloc, "integer is out of range");
    }
    return Kitsune::Json::JsonParser::make_NUMBER (length, jsonloc);
}

{int}+"."{int}*	{
    float value = atof( yytext );
    return Kitsune::Json::JsonParser::make_FLOAT(value, jsonloc);
}

{id}       return Kitsune::Json::JsonParser::make_IDENTIFIER(yytext, jsonloc);
.          driver.error(jsonloc, "invalid character");
<<EOF>>    return Kitsune::Json::JsonParser::make_END(jsonloc);

%%


void Kitsune::Json::JsonParserInterface::scan_begin(const std::string &inputString)
{
    Kitsune::Json::location newJsonloc;
    jsonloc = newJsonloc;
    yy_flex_debug = m_traceParsing;
    yy_scan_string(inputString.c_str());
}

void Kitsune::Json::JsonParserInterface::scan_end()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}


