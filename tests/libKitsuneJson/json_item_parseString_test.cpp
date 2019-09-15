/**
 *  @file    jsonItems_parseString_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "json_item_parseString_test.h"
#include <json_item.h>
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Json
{

JsonItem_ParseString_Test::JsonItem_ParseString_Test()
    : Kitsune::Common::UnitTest("JsonItems_ParseString_Test")
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
    std::string input("{item: "
                      "{ sub_item: \"test_value\"},"
                      "item2: "
                      "{ sub_item2: \"something\"},"
                      "loop: "
                      "[ {x :42 }, {x :42.0 }, 1234, {x :-42.0 }]"
                      "}");

    JsonItem paredItem;
    std::pair<bool, std::string> result = paredItem.parse(input);
    UNITTEST(result.first, true);
    std::string outputStringObjects = paredItem.toString(true);
    std::string compareObjects( "{\n"
                                "    item: {\n"
                                "        sub_item: \"test_value\"\n"
                                "    },\n"
                                "    item2: {\n"
                                "        sub_item2: \"something\"\n"
                                "    },\n"
                                "    loop: [\n"
                                "        {\n"
                                "            x: 42\n"
                                "        },\n"
                                "        {\n"
                                "            x: 42.000000\n"
                                "        },\n"
                                "        1234,\n"
                                "        {\n"
                                "            x: -42.000000\n"
                                "        }\n"
                                "    ]\n"
                                "}");
    UNITTEST(outputStringObjects, compareObjects);

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
    UNITTEST(result.first, false);

    std::string expectedError = "ERROR while parsing json-formated string \n"
            "parser-message: syntax error \n"
            "line-number: 4 \n"
            "position in line: 12 \n"
            "broken part in string: \":\" \n";
    UNITTEST(result.second, expectedError);
}

}  // namespace Json
}  // namespace Kitsune

