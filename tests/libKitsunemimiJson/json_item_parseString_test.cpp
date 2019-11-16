/**
 *  @file    jsonItems_parseString_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "json_item_parseString_test.h"
#include <libKitsunemimiJson/json_item.h>
#include <libKitsunemimiCommon/common_items/data_items.h>

namespace Kitsunemimi
{
namespace Json
{

JsonItem_ParseString_Test::JsonItem_ParseString_Test()
    : Kitsunemimi::Common::Test("JsonItems_ParseString_Test")
{
    parseString_test();
}

/**
 * parseString_test
 */
void
JsonItem_ParseString_Test::parseString_test()
{
    // positive test
    std::string input("{\"item\": "
                      "{ \"sub_item\": \"test_value\"},"
                      "\"item2\": "
                      "{ \"sub_item2\": \"something\"},"
                      "\"loop\": "
                      "[ {\"x\" :42 }, {\"x\" :42.0 }, 1234, {\"x\" :-42.0, \"y\": true, \"z\": false, \"w\": null}]"
                      "}");

    JsonItem paredItem;
    std::pair<bool, std::string> result = paredItem.parse(input);
    TEST_EQUAL(result.first, true);
    std::cout<<result.second<<std::endl;
    std::string outputStringMaps = paredItem.toString(true);
    std::string compareMaps("{\n"
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
                            "            \"w\": null,\n"
                            "            \"x\": -42.000000,\n"
                            "            \"y\": true,\n"
                            "            \"z\": false\n"
                            "        }\n"
                            "    ]\n"
                            "}");
    TEST_EQUAL(outputStringMaps, compareMaps);

    // negative test
    input = "{item: \n"
            "{ sub_item: \"test_value\"}, \n"
            "item2: \n"
            "[ sub_item2: \"something\"}, \n"  // error at the beginning of this line
            "loop: \n"
            "[ {x :\"test1\" }, {x :\"test2\" }, {x :\"test3\" }]\n"
            "}";

    JsonItem output;
    result = output.parse(input);
    TEST_EQUAL(result.first, false);

    std::string expectedError =
            "ERROR while parsing json-formated string \n"
            "parser-message: syntax error \n"
            "line-number: 4 \n"
            "position in line: 12 \n"
            "broken part in string: \":\" \n";
    TEST_EQUAL(result.second, expectedError);
}

}  // namespace Json
}  // namespace Kitsunemimi

