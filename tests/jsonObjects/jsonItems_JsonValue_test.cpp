/**
 *  @file    jsonItems_JsonValue_test.cpp
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

JsonItems_JsonValue_Test::JsonItems_JsonValue_Test()
    : Kitsune::CommonTest("JsonItems_JsonValue_Test")
{
    parseString_test();
    operator_test();
    get_test();
    getSize_test();
    remove_test();
    copy_test();
    print_test();
    getType_test();
    isValue_isObject_isArray_test();
    toValue_toObject_toArray_test();
    toString_toInt_toFloat_test();

    getValueType_test();
    setValue_test();
}

void
JsonItems_JsonValue_Test::parseString_test()
{

}

void
JsonItems_JsonValue_Test::operator_test()
{
    JsonValue defaultValue;

    bool isNullptr = defaultValue[1] == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue["1"] == nullptr;
    UNITTEST(isNullptr, true);
}

void
JsonItems_JsonValue_Test::get_test()
{
    JsonValue defaultValue;

    bool isNullptr = defaultValue.get(1) == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.get("1") == nullptr;
    UNITTEST(isNullptr, true);
}

void
JsonItems_JsonValue_Test::getSize_test()
{
    JsonValue defaultValue;
    UNITTEST(defaultValue.getSize(), 0);
}

void
JsonItems_JsonValue_Test::remove_test()
{
    JsonValue defaultValue;
    UNITTEST(defaultValue.remove(1), false);
    UNITTEST(defaultValue.remove(1), false);
}

void
JsonItems_JsonValue_Test::copy_test()
{
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    JsonValue* defaultValueCopy = dynamic_cast<JsonValue*>(defaultValue.copy());
    UNITTEST(defaultValue.m_stringValue, defaultValueCopy->m_stringValue);

    JsonValue* stringValueCopy = dynamic_cast<JsonValue*>(stringValue.copy());
    UNITTEST(stringValue.m_stringValue, stringValueCopy->m_stringValue);

    JsonValue* intValueCopy = dynamic_cast<JsonValue*>(intValue.copy());
    UNITTEST(intValue.m_intValue, intValueCopy->m_intValue);

    JsonValue* floatValueCopy = dynamic_cast<JsonValue*>(floatValue.copy());
    UNITTEST(floatValue.m_floatValue, floatValueCopy->m_floatValue);

    delete defaultValueCopy;
    delete stringValueCopy;
    delete intValueCopy;
    delete floatValueCopy;
}

void
JsonItems_JsonValue_Test::print_test()
{
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    UNITTEST(defaultValue.print(), "\"\"");
    UNITTEST(stringValue.print(), "\"test\"");
    UNITTEST(intValue.print(), "42");
    UNITTEST(floatValue.print(), "42.500000");
}

void
JsonItems_JsonValue_Test::getType_test()
{
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    UNITTEST(defaultValue.getType(), JsonItem::VALUE_TYPE);
    UNITTEST(stringValue.getType(), JsonItem::VALUE_TYPE);
    UNITTEST(intValue.getType(), JsonItem::VALUE_TYPE);
    UNITTEST(floatValue.getType(), JsonItem::VALUE_TYPE);
}

void
JsonItems_JsonValue_Test::isValue_isObject_isArray_test()
{
    JsonValue defaultValue;
    UNITTEST(defaultValue.isValue(), true);
    UNITTEST(defaultValue.isObject(), false);
    UNITTEST(defaultValue.isArray(), false);
}

void
JsonItems_JsonValue_Test::toValue_toObject_toArray_test()
{
    JsonValue defaultValue;

    bool isNullptr = defaultValue.toObject() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.toArray() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = defaultValue.toValue() == nullptr;
    UNITTEST(isNullptr, false);
}

void
JsonItems_JsonValue_Test::toString_toInt_toFloat_test()
{
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    UNITTEST(defaultValue.toString(), "");
    UNITTEST(defaultValue.toInt(), 0);
    UNITTEST(defaultValue.toFloat(), 0.0f);

    UNITTEST(stringValue.toString(), "test");
    UNITTEST(stringValue.toInt(), 0);
    UNITTEST(stringValue.toFloat(), 0.0f);

    UNITTEST(intValue.toString(), "42");
    UNITTEST(intValue.toInt(), 42);
    UNITTEST(intValue.toFloat(), 0.0f);

    UNITTEST(floatValue.toString(), "42.500000");
    UNITTEST(floatValue.toInt(), 0);
    UNITTEST(floatValue.toFloat(), 42.5f);
}

void
JsonItems_JsonValue_Test::getValueType_test()
{
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    UNITTEST(defaultValue.getValueType(), JsonItem::STRING_TYPE);
    UNITTEST(stringValue.getValueType(), JsonItem::STRING_TYPE);
    UNITTEST(intValue.getValueType(), JsonItem::INT_TYPE);
    UNITTEST(floatValue.getValueType(), JsonItem::FLOAT_TYPE);
}

void
JsonItems_JsonValue_Test::setValue_test()
{
    JsonValue defaultValue;

    defaultValue.setValue("test");
    UNITTEST(defaultValue.getValueType(), JsonItem::STRING_TYPE);
    UNITTEST(defaultValue.m_stringValue, "test");
    UNITTEST(defaultValue.m_intValue, 0);
    UNITTEST(defaultValue.m_floatValue, 0.0f);

    defaultValue.setValue(42);
    UNITTEST(defaultValue.getValueType(), JsonItem::INT_TYPE);
    UNITTEST(defaultValue.m_stringValue, "");
    UNITTEST(defaultValue.m_intValue, 42);
    UNITTEST(defaultValue.m_floatValue, 0.0f);

    defaultValue.setValue(42.5f);
    UNITTEST(defaultValue.getValueType(), JsonItem::FLOAT_TYPE);
    UNITTEST(defaultValue.m_stringValue, "");
    UNITTEST(defaultValue.m_intValue, 0);
    UNITTEST(defaultValue.m_floatValue, 42.5f);
}

}  // namespace Json
}  // namespace Kitsune
