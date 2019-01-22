/**
 *  @file    jsonArrayObjectsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include "jsonArrayObjectsTest.h"
#include <jsonObjects.h>

namespace Kitsune
{
namespace Json
{

JsonArrayObjectsTest::JsonArrayObjectsTest() : Kitsune::CommonTest("JsonArrayObjectsTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    removeTestCase();
    cleanupTestCase();
}

void JsonArrayObjectsTest::initTestCase()
{
    m_array = new JsonArray();
}

void JsonArrayObjectsTest::insertTestCase()
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

void JsonArrayObjectsTest::getTestCase()
{
    AbstractJson* value1 = (*m_array)["0"];
    UNITTEST(((JsonValue*)value1)->getString(), "test1");

    AbstractJson* value2 = (*m_array)[1];
    UNITTEST(((JsonValue*)value2)->getString(), "test2");
}

void JsonArrayObjectsTest::removeTestCase()
{
    UNITTEST(m_array->remove("1"), true);
    UNITTEST(m_array->getSize(), 1);
    UNITTEST(m_array->remove(0), true);
    UNITTEST(m_array->getSize(), 0);
    UNITTEST(m_array->remove(2), false);
}

void JsonArrayObjectsTest::cleanupTestCase()
{
    delete m_array;
}

}  // namespace Json
}  // namespace Kitsune
