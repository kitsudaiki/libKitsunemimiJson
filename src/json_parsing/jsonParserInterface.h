/**
 *  @file   jsonParserInterface.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONPARSERINTERFACE_HH
#define JSONPARSERINTERFACE_HH

#include <iostream>

namespace Kitsune
{
namespace Json
{
class location;
class JsonObject;

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
    void setOutput(JsonObject* output);
    JsonObject* getOutput() const;

    // Error handling.
    void error(const Kitsune::Json::location &location,
               const std::string& message);
    std::string getErrorMessage() const;

private:
    JsonObject* m_output;
    std::string m_errorMessage = "";
    std::string m_inputString = "";

    bool m_traceParsing = false;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONPARSERINTERFACE_HH
