/**
 *  @file    json_parser_interface.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSON_PARSER_INTERFACE_H
#define JSON_PARSER_INTERFACE_H

#include <iostream>

namespace Kitsune
{
namespace Common {
class DataObject;
}
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
    void setOutput(Common::DataObject* output);
    Common::DataObject* getOutput() const;

    // Error handling.
    void error(const Kitsune::Json::location &location,
               const std::string& message);
    std::string getErrorMessage() const;

private:
    Common::DataObject* m_output = nullptr;
    std::string m_errorMessage = "";
    std::string m_inputString = "";

    bool m_traceParsing = false;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSON_PARSER_INTERFACE_H
