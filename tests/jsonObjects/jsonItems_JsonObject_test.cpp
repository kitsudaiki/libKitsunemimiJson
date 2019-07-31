/**
 *  @file    jsonObjectObjectsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems_JsonObject_test.hpp"
#include <jsonItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonObjectObjectsTest::JsonObjectObjectsTest() : Kitsune::CommonTest("JsonObjectObjectsTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    removeTestCase();
    cleanupTestCase();
}

void JsonObjectObjectsTest::initTestCase()
{
    m_object = new JsonObject();
}

void JsonObjectObjectsTest::insertTestCase()
{
    UNITTEST(m_object->getSize(), 0);
    UNITTEST(m_object->getType(), JsonItem::OBJECT_TYPE);

    JsonValue* value1 = new JsonValue("test1");
    JsonValue* value2 = new JsonValue("test2");
    m_object->insert("poi1", value1);
    m_object->insert("poi2", value2);

    UNITTEST(m_object->getSize(), 2);
    std::string outputString = "";
    m_object->print(&outputString);
    std::string compare( "{\"poi1\":\"test1\",\"poi2\":\"test2\"}");
    UNITTEST(outputString, compare);
}

void JsonObjectObjectsTest::getTestCase()
{
    JsonItem* value1 = (*m_object)["poi1"];
    UNITTEST(((JsonValue*)value1)->toString(), "test1");

    JsonItem* value2 = (*m_object)[1];
    UNITTEST(((JsonValue*)value2)->toString(), "test2");

    std::vector<std::string> keys = m_object->getKeys();
    UNITTEST(keys.size(), 2);
    UNITTEST(keys.at(0), "poi1");
    UNITTEST(keys.at(1), "poi2");

    UNITTEST(m_object->contains("poi2"), true);
    UNITTEST(m_object->contains("poi3"), false);
}

void JsonObjectObjectsTest::removeTestCase()
{
    UNITTEST(m_object->remove("poi1"), true);
    UNITTEST(m_object->getSize(), 1);
    UNITTEST(m_object->remove(0), true);
    UNITTEST(m_object->getSize(), 0);
    UNITTEST(m_object->remove(2), false);
}

void JsonObjectObjectsTest::cleanupTestCase()
{
    delete m_object;
}

}  // namespace Json
}  // namespace Kitsune
