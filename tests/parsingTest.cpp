/**
 *  @file    parsingTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "parsingTest.h"
#include <jsonObjects.h>
#include <jsonItem.h>

namespace Kitsune
{
namespace Json
{

ParsingTest::ParsingTest() : Kitsune::CommonTest("ParsingTest")
{
    initTestCase();
    parserPositiveTest();
    parserNegativeTest();
    cleanupTestCase();
}

void ParsingTest::initTestCase()
{
}

void ParsingTest::parserPositiveTest()
{
    std::string input("{\"item\": "
                   "{ \"sub_item\": \"test_value\"},"
               "\"item2\": "
                   "{ \"sub_item2\": \"something\"},"
               "\"loop\": "
                   "[ {\"x\" :\"test1\" }, {\"x\" :\"test2\" }, {\"x\" :\"test3\" }]"
               "}");

    JsonObject* outputObjects = static_cast<JsonObject*>(AbstractJson::parseString(input));
    std::string outputStringObjects = "";
    outputObjects->print(&outputStringObjects);
    std::string compareObjects( "{\"item\":{\"sub_item\":\"test_value\"},\"item2\":{\"sub_item2\":\"something\"},\"loop\":[{\"x\":\"test1\"},{\"x\":\"test2\"},{\"x\":\"test3\"}]}");
    UNITTEST(outputStringObjects, compareObjects);

    JsonItem outputItem = JsonItem::parseString(input);
    std::string outputStringItem = "";
    outputItem.print(&outputStringItem);
    std::string compareItem( "{\"item\":{\"sub_item\":\"test_value\"},\"item2\":{\"sub_item2\":\"something\"},\"loop\":[{\"x\":\"test1\"},{\"x\":\"test2\"},{\"x\":\"test3\"}]}");
    UNITTEST(outputStringItem, compareItem);
}

void ParsingTest::parserNegativeTest()
{
    std::string input("{\"item\": "
                   "{ \"sub_item\": \"test_value\"}, \n"
               "\"item2\": \n"
                   "[ \"sub_item2\": \"something\"}, \n"  // error at the beginning of this line
               "\"loop\": \n"
                   "[ {\"x\" :\"test1\" }, {\"x\" :\"test2\" }, {\"x\" :\"test3\" }]\n"
               "}");

    AbstractJson* output = AbstractJson::parseString(input);
    bool success = false;
    if(output != nullptr) {
        success = true;
    }

    UNITTEST(success, false);
}

void ParsingTest::cleanupTestCase()
{
}

}  // namespace Json
}  // namespace Kitsune

