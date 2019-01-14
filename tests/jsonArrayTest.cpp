/**
 *  @file    jsonArrayTest.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include "jsonArrayTest.h"
#include <jsonItem.h>

namespace Kitsune
{
namespace Json
{

JsonArrayTest::JsonArrayTest() : Kitsune::CommonTest("JsonArrayTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    removeTestCase();
    cleanupTestCase();
}

void JsonArrayTest::initTestCase()
{
}

void JsonArrayTest::insertTestCase()
{
    std::vector<JsonItem> emptyVector;
    JsonItem item(emptyVector);

    UNITTEST(item.getSize(), 0);
    UNITTEST(item.isArray(), true);

    JsonItem value1("test1");
    JsonItem value2("test2");

    item.append(value1);
    item.append(value2);

    UNITTEST(item.getSize(), 2);
    std::string outputString = "";
    item.print(&outputString);
    std::string compare("[\"test1\",\"test2\"]");
    UNITTEST(outputString, compare);
}

void JsonArrayTest::getTestCase()
{
    std::vector<JsonItem> emptyVector;
    JsonItem item(emptyVector);
    JsonItem value1("test1");
    JsonItem value2("test2");
    item.append(value1);
    item.append(value2);

    JsonItem return1 = item["0"];
    UNITTEST(return1.getString(), "test1");

    JsonItem return2 = item[1];
    UNITTEST(return2.getString(), "test2");
}

void JsonArrayTest::removeTestCase()
{
    std::vector<JsonItem> emptyVector;
    JsonItem item(emptyVector);
    JsonItem value1("test1");
    JsonItem value2("test2");
    item.append(value1);
    item.append(value2);

    UNITTEST(item.remove("1"), true);
    UNITTEST(item.getSize(), 1);
    UNITTEST(item.remove(0), true);
    UNITTEST(item.getSize(), 0);
    UNITTEST(item.remove(2), false);
}

void JsonArrayTest::cleanupTestCase()
{
}

}  // namespace Json
}  // namespace Kitsune
