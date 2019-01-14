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
    m_item = new JsonItem(Json::ARRAY_TYPE);
}

void JsonArrayTest::insertTestCase()
{
    UNITTEST(m_item->getSize(), 0);
    UNITTEST(m_item->getType(), Json::ARRAY_TYPE);

    JsonItem value1(Json::VALUE_TYPE);
    JsonItem value2(Json::VALUE_TYPE);

    value1.setValue("test1");
    value2.setValue("test2");
    m_item->append(value1);
    m_item->append(value2);

    UNITTEST(m_item->getSize(), 2);
    std::string outputString = "";
    m_item->print(&outputString);
    std::string compare("[\"test1\",\"test2\"]");
    UNITTEST(outputString, compare);
}

void JsonArrayTest::getTestCase()
{
    JsonItem value1 = (*m_item)["0"];
    UNITTEST(value1.getString(), "test1");

    JsonItem value2 = (*m_item)[1];
    UNITTEST(value2.getString(), "test2");
}

void JsonArrayTest::removeTestCase()
{
    UNITTEST(m_item->remove("1"), true);
    UNITTEST(m_item->getSize(), 1);
    UNITTEST(m_item->remove(0), true);
    UNITTEST(m_item->getSize(), 0);
    UNITTEST(m_item->remove(2), false);
}

void JsonArrayTest::cleanupTestCase()
{
    delete m_item;
}

}  // namespace Json
}  // namespace Kitsune
