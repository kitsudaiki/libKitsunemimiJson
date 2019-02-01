/**
 *  @file    jsonValueItemTest.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonValueItemTest.h"
#include <jsonItem.h>

namespace Kitsune
{
namespace Json
{

JsonValueItemTest::JsonValueItemTest() : Kitsune::CommonTest("JsonValueItemTest")
{
    initTestCase();
    insertTestCase();
    getTestCase();
    cleanupTestCase();
}

void JsonValueItemTest::initTestCase()
{
    m_valueString = new JsonItem("2");
    m_valueInt = new JsonItem(42);
}

void JsonValueItemTest::insertTestCase()
{
    m_valueString->setValue("test");

    UNITTEST(m_valueString->isValue(), true);
    UNITTEST(m_valueInt->isValue(), true);
}

void JsonValueItemTest::getTestCase()
{
    UNITTEST(m_valueString->getString(), "test");
    UNITTEST(m_valueInt->getInt(), 42);
}

void JsonValueItemTest::cleanupTestCase()
{
    delete m_valueString;
    delete m_valueInt;
}

}  // namespace Json
}  // namespace Kitsune
