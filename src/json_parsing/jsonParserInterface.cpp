/**
 *  @file    jinja2ParserInterface.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include <json_parsing/jsonParserInterface.h>
#include <jsonObject.h>
#include <jsonParser.h>


# define YY_DECL \
    Kitsune::Json::JsonParser::symbol_type jsonlex (Kitsune::Json::JsonParserInterface& driver)
YY_DECL;

namespace Kitsune
{
namespace Json
{

/**
 * The class is the interface for the bison-generated parser.
 * It starts the parsing-process and store the returned values.
 *
 * @param traceParsing If set to true, the scanner prints all triggered rules.
 *                     It is only for better debugging.
 */
JsonParserInterface::JsonParserInterface(const bool traceParsing)
{
    m_traceParsing = traceParsing;
}

/**
 * Start the scanner and parser
 *
 * @param inputFile string which should be parsed
 * @return true, if parsing was successful, else false
 */
bool
JsonParserInterface::parse(const std::string &inputString)
{
    // init static variables for new run
    m_inRule = false;

    // init global values
    m_inputString = inputString;
    m_errorMessage = "";
    JsonObject* tempItem;
    m_output = tempItem;

    // run parser-code
    this->scan_begin(inputString);
    Kitsune::Json::JsonParser parser(*this);
    int res = parser.parse();
    this->scan_end();

    if(res != 0) {
        return false;
    }
    return true;
}

/**
 * Is called for the parser after successfully parsing the input-string
 *
 * @param output parser-output as QJsonArray
 */
void
JsonParserInterface::setOutput(JsonObject* output)
{
     m_output = output;
}

/**
 * getter for the json-output of the parser
 *
 * @return parser-output as QJsonArray
 */
JsonObject*
JsonParserInterface::getOutput() const
{
    return m_output;
}

/**
 * Is called from the parser in case of an error
 *
 * @param location location-object of the bison-parser,
 *                 which contains the informations of the location
 *                 of the syntax-error in the parsed string
 * @param message error-specific message from the parser
 */
void
JsonParserInterface::error(const Kitsune::Json::location& location,
                           const std::string& message)
{
    // get the broken part of the parsed string
    // const int errorStart = static_cast<int>(location.begin.column) - 1;
    // const int errorLength = static_cast<int>(location.end.column - location.begin.column);
    // const QString errorStringPart = m_inputString.mid(errorStart, errorLength);

    // build error-message
    // m_errorMessage =  "error while parsing jinja2-template \n";
    // m_errorMessage += "parser-message: " + QString(message.c_str()) + " \n";
    // m_errorMessage += "line-number: " + QString::number(location.begin.line) + " \n";
    // m_errorMessage += "broken part in template: " + errorStringPart + " \n";
}

/**
 * getter fot the error-message in case of an error while parsing
 *
 * @return error-message
 */
std::string
JsonParserInterface::getErrorMessage() const
{
    return m_errorMessage;
}

}  // namespace Json
}  // namespace Kitsune
