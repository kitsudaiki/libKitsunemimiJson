/**
 *  @file    json_parser_interface.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef JSON_PARSER_INTERFACE_H
#define JSON_PARSER_INTERFACE_H

#include <iostream>

namespace Kitsunemimi
{
class DataItem;
namespace Json
{
class location;

class JsonParserInterface
{

public:
    JsonParserInterface(const bool traceParsing = false);
    ~JsonParserInterface();

    // connection the the scanner and parser
    void scan_begin(const std::string &inputString);
    void scan_end();
    bool parse(const std::string &inputString);
    std::string removeQuotes(std::string input);

    // output-handling
    void setOutput(DataItem* output);
    DataItem* getOutput() const;

    // Error handling.
    void error(const Kitsunemimi::Json::location &location,
               const std::string& message);
    std::string getErrorMessage() const;

private:
    DataItem* m_output = nullptr;
    std::string m_errorMessage = "";
    std::string m_inputString = "";

    bool m_traceParsing = false;
};

}  // namespace Json
}  // namespace Kitsunemimi

#endif // JSON_PARSER_INTERFACE_H
