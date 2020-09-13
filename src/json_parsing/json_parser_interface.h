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
#include <mutex>

namespace Kitsunemimi
{
class DataItem;
namespace Json
{
class location;

class JsonParserInterface
{

public:
    static JsonParserInterface* getInstance();
    ~JsonParserInterface();

    // connection the the scanner and parser
    void scan_begin(const std::string &inputString);
    void scan_end();
    DataItem* parse(const std::string &inputString, std::string &errorMessage);
    const std::string removeQuotes(const std::string &input);

    // output-handling
    void setOutput(DataItem* output);

    // Error handling.
    void error(const Kitsunemimi::Json::location &location,
               const std::string& message);

private:
    JsonParserInterface(const bool traceParsing = false);

    static JsonParserInterface* m_instance;

    DataItem* m_output = nullptr;
    std::string m_errorMessage = "";
    std::string m_inputString = "";
    std::mutex m_lock;

    bool m_traceParsing = false;
};

}  // namespace Json
}  // namespace Kitsunemimi

#endif // JSON_PARSER_INTERFACE_H
