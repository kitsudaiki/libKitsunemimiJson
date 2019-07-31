/**
 *  @file    jsonItems_JsonArray_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems_JsonArray_test.hpp"
#include <jsonItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonItems_JsonArray_Test::JsonItems_JsonArray_Test()
    : Kitsune::CommonTest("JsonItems_JsonArray_Test")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    removeTestCase();
    cleanupTestCase();
}

void JsonItems_JsonArray_Test::initTestCase()
{
    m_array = new JsonArray();
}

void JsonItems_JsonArray_Test::insertTestCase()
{
    UNITTEST(m_array->getSize(), 0);
    UNITTEST(m_array->getType(), JsonItem::ARRAY_TYPE);

    JsonValue* value1 = new JsonValue("test1");
    JsonValue* value2 = new JsonValue("test2");
    m_array->append(value1);
    m_array->append(value2);

    UNITTEST(m_array->getSize(), 2);
    std::string outputString = "";
    m_array->print(&outputString);
    std::string compare( "[\"test1\",\"test2\"]");
    UNITTEST(outputString, compare);
}

void JsonItems_JsonArray_Test::getTestCase()
{
    JsonItem* value1 = (*m_array)["0"];
    UNITTEST(((JsonValue*)value1)->toString(), "test1");

    JsonItem* value2 = (*m_array)[1];
    UNITTEST(((JsonValue*)value2)->toString(), "test2");
}

void JsonItems_JsonArray_Test::removeTestCase()
{
    UNITTEST(m_array->remove("1"), true);
    UNITTEST(m_array->getSize(), 1);
    UNITTEST(m_array->remove(0), true);
    UNITTEST(m_array->getSize(), 0);
    UNITTEST(m_array->remove(2), false);
}

void JsonItems_JsonArray_Test::cleanupTestCase()
{
    delete m_array;
}

}  // namespace Json
}  // namespace Kitsune
