/**
 *  @file    jsonArrayTest.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include "jsonArrayTest.h"
#include <jsonObjects.h>

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
    m_array = new JsonArray();
}

void JsonArrayTest::insertTestCase()
{
    UNITTEST(m_array->getSize(), 0);
    UNITTEST(m_array->getType(), AbstractJson::ARRAY_TYPE);

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

void JsonArrayTest::getTestCase()
{
    AbstractJson* value1 = (*m_array)["0"];
    UNITTEST(((JsonValue*)value1)->getString(), "test1");

    AbstractJson* value2 = (*m_array)[1];
    UNITTEST(((JsonValue*)value2)->getString(), "test2");
}

void JsonArrayTest::removeTestCase()
{
    UNITTEST(m_array->remove("1"), true);
    UNITTEST(m_array->getSize(), 1);
    UNITTEST(m_array->remove(0), true);
    UNITTEST(m_array->getSize(), 0);
    UNITTEST(m_array->remove(2), false);
}

void JsonArrayTest::cleanupTestCase()
{
    delete m_array;
}

}
}
