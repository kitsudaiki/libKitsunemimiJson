/**
 *  @file    jsonParserInterface.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONPARSERINTERFACE_HH
#define JSONPARSERINTERFACE_HH

#include <iostream>
#include <jsonItems.h>

namespace Kitsune
{
namespace Json
{
class location;

class JsonParserInterface
{

public:
    JsonParserInterface(const bool traceParsing = false);

    // connection the the scanner and parser
    void scan_begin(const std::string &inputString);
    void scan_end();
    bool parse(const std::string &inputString);
    std::string removeQuotes(std::string input);

    // output-handling
    void setOutput(JsonItem output);
    JsonItem getOutput() const;

    // Error handling.
    void error(const Kitsune::Json::location &location,
               const std::string& message);
    std::string getErrorMessage() const;

private:
    JsonItem m_output;
    std::string m_errorMessage = "";
    std::string m_inputString = "";

    bool m_traceParsing = false;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONPARSERINTERFACE_HH
