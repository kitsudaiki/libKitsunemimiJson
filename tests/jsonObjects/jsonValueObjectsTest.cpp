/**
 *  @file    jsonValueObjectsTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonValueObjectsTest.h"
#include <jsonItems.h>

namespace Kitsune
{
namespace Json
{

JsonValueObjectsTest::JsonValueObjectsTest() : Kitsune::CommonTest("JsonValueObjectsTest")
{
    initTestCase();
    cleanupTestCase();
}

void JsonValueObjectsTest::initTestCase()
{
    JsonItem m_valueString(42);
    JsonItem m_valueInt(42);
    JsonItem m_valueFloat(42.42f);

    m_valueString.setValue("test");

    UNITTEST(m_valueString.getType(), JsonItem::STRING_TYPE);
    UNITTEST(m_valueInt.getType(), JsonItem::INT_TYPE);
    UNITTEST(m_valueFloat.getType(), JsonItem::FLOAT_TYPE);

    UNITTEST(m_valueString.toString(), "test");
    UNITTEST(m_valueInt.toInt(), 42);
    UNITTEST(m_valueFloat.toFloat(), 42.42f);
}

void JsonValueObjectsTest::cleanupTestCase()
{

}

}  // namespace Json
}  // namespace Kitsune
