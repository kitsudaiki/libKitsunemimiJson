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
    : Kitsunemimi::MemoryLeakTestHelpter("JsonItems_ParseString_Test")
{
    parseString_test();
}

/**
 * parseString_test
 */
void
JsonItem_ParseString_Test::parseString_test()
{

    std::string input1("{\"item\": "
                      "{ \"sub_item\": \"test_value\"},"
                      "\"item2\": "
                      "{ \"sub_item2\": \"something\"},"
                      "\"loop\": "
                      "[ {\"x\" :42 }, {\"x\" :42.0 }, 1234, {\"x\" :-42.0, \"y\": true, \"z\": false, \"w\": null}]"
                      "}");
    std::string input2 = "[ {x :\"test1\" }, {x :\"test2\" }, {x :\"test3\" }]";
    ErrorContainer error;

    // make one untested run to allow parser to allocate one-time global stuff
    JsonItem* paredItem = new JsonItem();
    paredItem->parse(input1, error);
    delete paredItem;

    // parse valid string
    REINIT_TEST();
    paredItem = new JsonItem();
    paredItem->parse(input1, error);
    paredItem->parse(input1, error);
    paredItem->parse(input2, error);
    delete paredItem;
    CHECK_MEMORY();


    /*
    PARSING INVALID STRING HAS MEMORY-LEAK. See issue:
    https://github.com/kitsudaiki/libKitsunemimiJson/issues/49

    input1 = "{item: \n"
             "{ sub_item: \"test_value\"}, \n"
             "item2: \n"
             "[ sub_item2: \"something\"}, \n"  // error at the beginning of this line
             "loop: \n"
             "[ {x :\"test1\" }, {x :\"test2\" }, {x :\"test3\" }]\n"
             "}";

    // parse invalid string
    REINIT_TEST();
    JsonItem* output = new JsonItem();
    output->parse(input1, error);
    error._errorMessages.clear();
    error._possibleSolution.clear();
    delete output;
    CHECK_MEMORY();*/
}

}  // namespace Json
}  // namespace Kitsunemimi

