/**
 *  @file    jsonArrayObjectsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonArrayObjectsTest.h"
#include <jsonItems.h>

namespace Kitsune
{
namespace Json
{

JsonArrayObjectsTest::JsonArrayObjectsTest() : Kitsune::CommonTest("JsonArrayObjectsTest")
{
    initTestCase();
    insertTestCase();
    cleanupTestCase();
}

void JsonArrayObjectsTest::initTestCase()
{
}

void JsonArrayObjectsTest::insertTestCase()
{
    JsonItem testArray;

    UNITTEST(testArray.getSize(), 0);
    UNITTEST(testArray.getType(), JsonItem::ARRAY_TYPE);

    JsonItem value1("test1");
    JsonItem value2("test2");
    testArray.append(value1);
    testArray.append(value2);

    UNITTEST(testArray.getSize(), 2);
    std::string outputString = "";
    testArray.print(&outputString);
    std::string compare( "[\"test1\",\"test2\"]");
    UNITTEST(outputString, compare);

    JsonItem value3 = testArray[0];
    UNITTEST(value3.toString(), "test1");

    JsonItem value4 = testArray[1];
    UNITTEST(value4.toString(), "test2");

    UNITTEST(testArray.remove(1), true);
    UNITTEST(testArray.getSize(), 1);
    UNITTEST(testArray.remove(0), true);
    UNITTEST(testArray.getSize(), 0);
    UNITTEST(testArray.remove(2), false);
}

void JsonArrayObjectsTest::cleanupTestCase()
{
}

}  // namespace Json
}  // namespace Kitsune
