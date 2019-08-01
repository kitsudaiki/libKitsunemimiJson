/**
 *  @file    jsonItems_parseString_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems_parseString_test.h"
#include <jsonItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonItems_ParseString_Test::JsonItems_ParseString_Test()
    : Kitsune::CommonTest("JsonItems_ParseString_Test")
{
    parserPositiveTest();
    parserNegativeTest();
}

void JsonItems_ParseString_Test::parserPositiveTest()
{
    std::string input("{\"item\": "
                      "{ \"sub_item\": \"test_value\"},"
                      "\"item2\": "
                      "{ \"sub_item2\": \"something\"},"
                      "\"loop\": "
                      "[ {\"x\" :42 }, {\"x\" :42.0 }, 1234, {\"x\" :-42.0 }]"
                      "}");

    JsonObject* outputObjects = static_cast<JsonObject*>(JsonItem::parseString(input));
    std::string outputStringObjects = "";
    outputObjects->print(&outputStringObjects, true);
    std::string compareObjects( "{\n"
                                "    \"item\": {\n"
                                "        \"sub_item\": \"test_value\"\n"
                                "    },\n"
                                "    \"item2\": {\n"
                                "        \"sub_item2\": \"something\"\n"
                                "    },\n"
                                "    \"loop\": [\n"
                                "        {\n"
                                "            \"x\": 42\n"
                                "        },\n"
                                "        {\n"
                                "            \"x\": 42.000000\n"
                                "        },\n"
                                "        1234,\n"
                                "        {\n"
                                "            \"x\": -42.000000\n"
                                "        }\n"
                                "    ]\n"
                                "}");
    UNITTEST(outputStringObjects, compareObjects);
}

void JsonItems_ParseString_Test::parserNegativeTest()
{
    std::string input("{\"item\": "
                      "{ \"sub_item\": \"test_value\"}, \n"
                      "\"item2\": \n"
                      "[ \"sub_item2\": \"something\"}, \n"  // error at the beginning of this line
                      "\"loop\": \n"
                      "[ {\"x\" :\"test1\" }, {\"x\" :\"test2\" }, {\"x\" :\"test3\" }]\n"
                      "}");

    JsonItem* output = JsonItem::parseString(input);
    bool success = false;
    if(output != nullptr) {
        success = true;
    }

    UNITTEST(success, false);
}

}  // namespace Json
}  // namespace Kitsune

