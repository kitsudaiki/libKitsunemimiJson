/**
 *  @file    jsonItems_parseString_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItem_parseString_test.hpp"
#include <jsonItem.hpp>
#include <data_structure/dataItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonItems_ParseString_Test::JsonItems_ParseString_Test()
    : Kitsune::Common::Test("JsonItems_ParseString_Test")
{
    parseString_test();
}

/**
 * parseString_test
 */
void
JsonItems_ParseString_Test::parseString_test()
{
    // positive test
    std::string input("{\"item\": "
                      "{ \"sub_item\": \"test_value\"},"
                      "\"item2\": "
                      "{ \"sub_item2\": \"something\"},"
                      "\"loop\": "
                      "[ {\"x\" :42 }, {\"x\" :42.0 }, 1234, {\"x\" :-42.0 }]"
                      "}");

    JsonItem paredItem;
    std::pair<bool, std::string> result = paredItem.parse(input);
    UNITTEST(result.first, true);
    std::string outputStringObjects = paredItem.print(true);
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

    // negative test
    input = "{\"item\": "
            "{ \"sub_item\": \"test_value\"}, \n"
            "\"item2\": \n"
            "[ \"sub_item2\": \"something\"}, \n"  // error at the beginning of this line
            "\"loop\": \n"
            "[ {\"x\" :\"test1\" }, {\"x\" :\"test2\" }, {\"x\" :\"test3\" }]\n"
            "}";

    JsonItem output;
    result = output.parse(input);
    UNITTEST(result.first, false);
}

}  // namespace Json
}  // namespace Kitsune

