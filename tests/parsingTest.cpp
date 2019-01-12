/**
 *  @file    parsingTest.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include "parsingTest.h"
#include <jsonObjects.h>

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

    JsonObject* output = static_cast<JsonObject*>(AbstractJson::parseString(input));

    std::string outputString = "";
    output->print(&outputString);
    std::string compare( "{\"item\":{\"sub_item\":\"test_value\"},\"item2\":{\"sub_item2\":\"something\"},\"loop\":[{\"x\":\"test1\"},{\"x\":\"test2\"},{\"x\":\"test3\"}]}");
    UNITTEST(outputString, compare);
}

void ParsingTest::parserNegativeTest()
{
    std::string input("{\"item\": "
                   "{ \"sub_item\": \"test_value\"},"
               "\"item2\": "
                   "[ \"sub_item2\": \"something\"},"  // error at the beginning of this line
               "\"loop\": "
                   "[ {\"x\" :\"test1\" }, {\"x\" :\"test2\" }, {\"x\" :\"test3\" }]"
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

}
}
