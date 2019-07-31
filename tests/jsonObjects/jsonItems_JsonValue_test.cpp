/**
 *  @file    jsonValueObjectsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItems_JsonValue_test.hpp"
#include <jsonItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonValueObjectsTest::JsonValueObjectsTest() : Kitsune::CommonTest("JsonValueObjectsTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    cleanupTestCase();
}

void JsonValueObjectsTest::initTestCase()
{
    m_valueString = new JsonValue(42);
    m_valueInt = new JsonValue(42);
    m_valueFloat = new JsonValue(42.42f);
}

void JsonValueObjectsTest::insertTestCase()
{
    m_valueString->setValue("test");

    UNITTEST(m_valueString->getValueType(), JsonItem::STRING_TYPE);
    UNITTEST(m_valueInt->getValueType(), JsonItem::INT_TYPE);
    UNITTEST(m_valueFloat->getValueType(), JsonItem::FLOAT_TYPE);
}

void JsonValueObjectsTest::getTestCase()
{
    UNITTEST(m_valueString->toString(), "test");
    UNITTEST(m_valueInt->toInt(), 42);
    UNITTEST(m_valueFloat->toFloat(), 42.42f);
}

void JsonValueObjectsTest::cleanupTestCase()
{
    delete m_valueString;
    delete m_valueInt;
    delete m_valueFloat;
}

}  // namespace Json
}  // namespace Kitsune
