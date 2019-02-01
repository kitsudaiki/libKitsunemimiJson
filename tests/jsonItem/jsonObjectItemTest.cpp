/**
 *  @file    jsonObjectItemTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonObjectItemTest.h"
#include <jsonItem.h>

namespace Kitsune
{
namespace Json
{

JsonObjectItemTest::JsonObjectItemTest() : Kitsune::CommonTest("JsonObjectItemTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    removeTestCase();
    cleanupTestCase();
}

void JsonObjectItemTest::initTestCase()
{
    std::map<std::string, JsonItem> emptyMap;
    m_item = new JsonItem(emptyMap);
}

void JsonObjectItemTest::insertTestCase()
{
    JsonItem item(*m_item);

    UNITTEST(item.getSize(), 0);
    UNITTEST(item.isObject(), true);

    JsonItem value1("test1");
    JsonItem value2("test2");
    item.insert("poi1", value1);
    item.insert("poi2", value2);

    UNITTEST(item.getSize(), 2);
    std::string outputString = "";
    item.print(&outputString);
    std::string compare( "{\"poi1\":\"test1\",\"poi2\":\"test2\"}");
    UNITTEST(outputString, compare);

    *m_item = item;
}

void JsonObjectItemTest::getTestCase()
{
    JsonItem item(*m_item);

    JsonItem value1 = item["poi1"];
    UNITTEST(value1.getString(), "test1");

    JsonItem value2 = item[1];
    UNITTEST(value2.getString(), "test2");
}

void JsonObjectItemTest::removeTestCase()
{
    JsonItem item(*m_item);

    UNITTEST(item.remove("poi1"), true);
    UNITTEST(item.getSize(), 1);
    UNITTEST(item.remove(0), true);
    UNITTEST(item.getSize(), 0);
    UNITTEST(item.remove(2), false);
}

void JsonObjectItemTest::cleanupTestCase()
{
    delete m_item;
}

}  // namespace Json
}  // namespace Kitsune
