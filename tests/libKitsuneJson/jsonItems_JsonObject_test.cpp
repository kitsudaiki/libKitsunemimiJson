/**
 *  @file    jsonItems_JsonObject_test.cpp
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

JsonItems_JsonObject_Test::JsonItems_JsonObject_Test()
    : Kitsune::CommonTest("JsonItems_JsonObject_Test")
{
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

    // object-exclusive
    insert_test();
    getString_getInt_getFloat_test();
    getKeys_test();
    getValues_test();
    contains_test();
}

/**
 * operator_test
 */
void
JsonItems_JsonObject_Test::operator_test()
{
    JsonObject object = initTestObject();

    UNITTEST(object[0]->toString(), "test");
    UNITTEST(object["hmm"]->toInt(), 42);

    // negative tests
    bool isNullptr = object[10] == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = object["k"] == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * get_test
 */
void
JsonItems_JsonObject_Test::get_test()
{
    JsonObject object = initTestObject();

    UNITTEST(object.get(0)->toString(), "test");
    UNITTEST(object.get("hmm")->toInt(), 42);

    // negative tests
    bool isNullptr = object.get(10) == nullptr;
    UNITTEST(isNullptr, true);
    isNullptr = object.get("k") == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * getSize_test
 */
void
JsonItems_JsonObject_Test::getSize_test()
{
    JsonObject object = initTestObject();
    UNITTEST(object.getSize(), 4);
}

/**
 * remove_test
 */
void
JsonItems_JsonObject_Test::remove_test()
{
    JsonObject object = initTestObject();
    UNITTEST(object.remove(0), true);
    UNITTEST(object.remove("hmm"), true);

    UNITTEST(object.get(1)->toString(), "42.500000");
    UNITTEST(object.getSize(), 2);

    // negative tests
    UNITTEST(object.remove(10), false);
}

/**
 * copy_test
 */
void
JsonItems_JsonObject_Test::copy_test()
{
    JsonObject object = initTestObject();

    JsonObject* objectCopy = dynamic_cast<JsonObject*>(object.copy());

    bool isNullptr = objectCopy == nullptr;
    UNITTEST(isNullptr, false);

    UNITTEST(object.print(), objectCopy->print());

    delete objectCopy;
}

/**
 * print_test
 */
void
JsonItems_JsonObject_Test::print_test()
{
    JsonObject object = initTestObject();

    std::string compare = "{\"asdf\":\"test\",\"hmm\":42,\"poi\":\"\",\"xyz\":42.500000}";
    UNITTEST(object.print(), compare);

    compare = "{\n"
              "    \"asdf\": \"test\",\n"
              "    \"hmm\": 42,\n"
              "    \"poi\": \"\",\n"
              "    \"xyz\": 42.500000\n"
              "}";
    UNITTEST(object.print(nullptr, true), compare);
}

/**
 * getType_test
 */
void
JsonItems_JsonObject_Test::getType_test()
{
    JsonObject object = initTestObject();
    UNITTEST(object.getType(), JsonItem::OBJECT_TYPE);
}

/**
 * isValue_isObject_isArray_test
 */
void
JsonItems_JsonObject_Test::isValue_isObject_isArray_test()
{
    JsonObject object = initTestObject();
    UNITTEST(object.isValue(), false);
    UNITTEST(object.isObject(), true);
    UNITTEST(object.isArray(), false);
}

/**
 * toValue_toObject_toArray_test
 */
void
JsonItems_JsonObject_Test::toValue_toObject_toArray_test()
{
    JsonObject object = initTestObject();

    bool isNullptr = object.toObject() == nullptr;
    UNITTEST(isNullptr, false);

    isNullptr = object.toArray() == nullptr;
    UNITTEST(isNullptr, true);

    isNullptr = object.toValue() == nullptr;
    UNITTEST(isNullptr, true);
}

/**
 * toString_toInt_toFloat_test
 */
void
JsonItems_JsonObject_Test::toString_toInt_toFloat_test()
{
    JsonObject object = initTestObject();
    UNITTEST(object.toString(), "");
    UNITTEST(object.toInt(), 0);
    UNITTEST(object.toFloat(), 0.0f);
}

/**
 * insert_test
 */
void
JsonItems_JsonObject_Test::insert_test()
{
    JsonObject object;
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    UNITTEST(object.insert("poi", defaultValue.copy()), true);
    UNITTEST(object.insert("asdf", stringValue.copy()), true);
    UNITTEST(object.insert("hmm", intValue.copy()), true);
    UNITTEST(object.insert("xyz", floatValue.copy()), true);
}

/**
 * getString_getInt_getFloat_test
 */
void
JsonItems_JsonObject_Test::getString_getInt_getFloat_test()
{
    JsonObject object = initTestObject();

    UNITTEST(object.getString("asdf"), "test");
    UNITTEST(object.getInt("hmm"), 42);
    UNITTEST(object.getFloat("xyz"), 42.5f);
}

/**
 * getKeys_test
 */
void
JsonItems_JsonObject_Test::getKeys_test()
{
    JsonObject object = initTestObject();

    std::vector<std::string> keys = object.getKeys();
    UNITTEST(keys.size(), 4);
    UNITTEST(keys.at(0), "asdf");
    UNITTEST(keys.at(1), "hmm");
    UNITTEST(keys.at(2), "poi");
    UNITTEST(keys.at(3), "xyz");
}

/**
 * getValues_test
 */
void
JsonItems_JsonObject_Test::getValues_test()
{
    JsonObject object = initTestObject();

    std::vector<JsonItem*> values = object.getValues();
    UNITTEST(values.size(), 4);
    UNITTEST(values.at(0)->toString(), "test");
    UNITTEST(values.at(1)->toString(), "42");
    UNITTEST(values.at(2)->toString(), "");
    UNITTEST(values.at(3)->toString(), "42.500000");
}

/**
 * contains_test
 */
void
JsonItems_JsonObject_Test::contains_test()
{
    JsonObject object = initTestObject();
    UNITTEST(object.contains("poi"), true);
    UNITTEST(object.contains("asdf"), true);
    UNITTEST(object.contains("hmm"), true);
    UNITTEST(object.contains("xyz"), true);

    UNITTEST(object.contains("fail"), false);
}

/**
 * create test json-object
 *
 * @return json-object for tests
 */
JsonObject
JsonItems_JsonObject_Test::initTestObject()
{
    JsonObject object;
    JsonValue defaultValue;
    JsonValue stringValue("test");
    JsonValue intValue(42);
    JsonValue floatValue(42.5f);

    object.insert("poi", defaultValue.copy());
    object.insert("asdf", stringValue.copy());
    object.insert("hmm", intValue.copy());
    object.insert("xyz", floatValue.copy());

    return object;
}

}  // namespace Json
}  // namespace Kitsune
