/**
 *  @file    jsonValueTest.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include "jsonValueTest.h"
#include <jsonObjects.h>

namespace Kitsune
{
namespace Json
{

JsonValueTest::JsonValueTest() : Kitsune::CommonTest("JsonValueTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    cleanupTestCase();
}

void JsonValueTest::initTestCase()
{
    m_valueString = new JsonValue(42);
    m_valueInt = new JsonValue(42);
}

void JsonValueTest::insertTestCase()
{
    m_valueString->setValue("test");

    UNITTEST(m_valueString->getType(), AbstractJson::STRING_TYPE);
    UNITTEST(m_valueInt->getType(), AbstractJson::INT_TYPE);
}

void JsonValueTest::getTestCase()
{
    UNITTEST(m_valueString->getString(), "test");
    UNITTEST(m_valueInt->getInt(), 42);
}

void JsonValueTest::cleanupTestCase()
{
    delete m_valueString;
    delete m_valueInt;
}

}
}
