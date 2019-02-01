/**
 *  @file    jsonArrayItemTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonArrayItemTest.h"
#include <jsonItem.h>

namespace Kitsune
{
namespace Json
{

JsonArrayItemTest::JsonArrayItemTest() : Kitsune::CommonTest("JsonArrayItemTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    removeTestCase();
    cleanupTestCase();
}

void JsonArrayItemTest::initTestCase()
{
    std::vector<JsonItem> emptyVector;
    m_item = new JsonItem(emptyVector);
}

void JsonArrayItemTest::insertTestCase()
{
    JsonItem item(*m_item);

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

    *m_item = item;
}

void JsonArrayItemTest::getTestCase()
{
    JsonItem item(*m_item);

    JsonItem return1 = item["0"];
    UNITTEST(return1.getString(), "test1");

    JsonItem return2 = item[1];
    UNITTEST(return2.getString(), "test2");
}

void JsonArrayItemTest::removeTestCase()
{
    JsonItem item(*m_item);

    UNITTEST(item.remove("1"), true);
    UNITTEST(item.getSize(), 1);
    UNITTEST(item.remove(0), true);
    UNITTEST(item.getSize(), 0);
    UNITTEST(item.remove(2), false);
}

void JsonArrayItemTest::cleanupTestCase()
{
    delete m_item;
}

}  // namespace Json
}  // namespace Kitsune
