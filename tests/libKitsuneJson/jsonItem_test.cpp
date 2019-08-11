/**
 *  @file    jsonItem_test.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include "jsonItem_test.hpp"
#include <data_structure/dataItems.hpp>

namespace Kitsune
{
namespace Json
{

JsonItem_Test::JsonItem_Test()
    : Kitsune::Common::Test("JsonItem_Test")
{
    constructor_test();
    assigmentOperator_test();
    setValue_test();
    insert_test();
    append_test();
    replaceItem_test();

    getItemContent_test();
    get_test();
    getString_getInt_getFloat_test();

    getSize_test();
    getKeys_test();
    contains_test();

    isValid_test();
    isObject_isArray_isValue_test();

    remove_test();
}

/**
 * constructor_test
 */
void
JsonItem_Test::constructor_test()
{
    JsonItem emptyItem;
    UNITTEST(emptyItem.isValid(), false);

    std::map<std::string, JsonItem> emptyMap;
    JsonItem objectItem(emptyMap);
    UNITTEST(objectItem.isObject(), true);

    JsonItem objectCopyItem(objectItem);
    UNITTEST(objectCopyItem.isObject(), true);

    std::vector<JsonItem> emptyArray;
    JsonItem arrayItem(emptyArray);
    UNITTEST(arrayItem.isArray(), true);

    JsonItem stringItem("test");
    UNITTEST(stringItem.isValue(), true);

    JsonItem intItem(42);
    UNITTEST(intItem.isValue(), true);

    JsonItem floatItem(42.0f);
    UNITTEST(floatItem.isValue(), true);
}

/**
 * assigmentOperator_test
 */
void
JsonItem_Test::assigmentOperator_test()
{
    JsonItem testItem = getTestItem();

    JsonItem copy;
    copy = testItem;

    UNITTEST(copy.print(), testItem.print());
}

/**
 * setValue_test
 */
void
JsonItem_Test::setValue_test()
{
    JsonItem testItem;
    UNITTEST(testItem.setValue("test"), true);
    UNITTEST(testItem.setValue(42), true);
    UNITTEST(testItem.setValue(42.0f), true);

    UNITTEST(testItem.isValid(), true);


    // negative test
    std::map<std::string, JsonItem> emptyMap;
    JsonItem objectItem(emptyMap);
    UNITTEST(objectItem.setValue("test"), false);
}

/**
 * insert_test
 */
void
JsonItem_Test::insert_test()
{
    JsonItem testItem;
    UNITTEST(testItem.insert("key", JsonItem(42)), true);
    UNITTEST(testItem.insert("key", JsonItem("24"), true), true);
    UNITTEST(testItem["key"].getString(), "24");
    UNITTEST(testItem.isObject(), true);

    // negative test
    UNITTEST(testItem.insert("key", JsonItem(43)), false);
    UNITTEST(testItem.insert("fail", JsonItem()), false);
}

/**
 * append_test
 */
void
JsonItem_Test::append_test()
{
    JsonItem testItem;
    UNITTEST(testItem.append(JsonItem(42)), true);
    UNITTEST(testItem.isArray(), true);
    UNITTEST(testItem[0].getInt(), 42);

    // negative test
    UNITTEST(testItem.append(JsonItem()), false);
}

/**
 * replaceItem_test
 */
void
JsonItem_Test::replaceItem_test()
{
    JsonItem testItem;
    testItem.append(JsonItem(42));
    testItem.append(JsonItem("42"));
    UNITTEST(testItem[0].getString(), "42");
    UNITTEST(testItem.replaceItem(0, JsonItem("ok")), true);
    UNITTEST(testItem[0].getString(), "ok");

    // negative test
    UNITTEST(testItem.replaceItem(10, JsonItem("fail")), false);
    UNITTEST(testItem.replaceItem(0, JsonItem()), false);
}

/**
 * getItemContent_test
 */
void
JsonItem_Test::getItemContent_test()
{
    JsonItem testItem = getTestItem();
    Common::DataItem* itemPtr = testItem.getItemContent();

    UNITTEST(itemPtr->print(nullptr, true), testItem.print(true));
}

/**
 * get_test
 */
void
JsonItem_Test::get_test()
{
    JsonItem testItem = getTestItem();
    UNITTEST(testItem["loop"][0]["x"].getString(), "42");
    UNITTEST(testItem.get("loop").get(0).get("x").getString(), "42");
}

/**
 * getString_getInt_getFloat_test
 */
void
JsonItem_Test::getString_getInt_getFloat_test()
{
    JsonItem stringValue("test");
    JsonItem intValue(42);
    JsonItem floatValue(42.5f);

    // string-value
    UNITTEST(stringValue.getString(), "test");
    UNITTEST(stringValue.getInt(), 0);
    UNITTEST(stringValue.getFloat(), 0.0f);

    // int-value
    UNITTEST(intValue.getString(), "42");
    UNITTEST(intValue.getInt(), 42);
    UNITTEST(intValue.getFloat(), 0.0f);

    // float-value
    UNITTEST(floatValue.getString(), "42.500000");
    UNITTEST(floatValue.getInt(), 0);
    UNITTEST(floatValue.getFloat(), 42.5f);
}

/**
 * getSize_test
 */
void
JsonItem_Test::getSize_test()
{
    JsonItem testItem = getTestItem();
    UNITTEST(testItem.getSize(), 3);
}

/**
 * getKeys_test
 */
void
JsonItem_Test::getKeys_test()
{
    JsonItem testItem = getTestItem();
    std::vector<std::string> keys = testItem.getKeys();
    UNITTEST(keys.size(), 3);
    UNITTEST(keys.at(0), "item");
    UNITTEST(keys.at(1), "item2");
    UNITTEST(keys.at(2), "loop");
}

/**
 * contains_test
 */
void
JsonItem_Test::contains_test()
{
    JsonItem testItem = getTestItem();
    UNITTEST(testItem.contains("item"), true);
    UNITTEST(testItem.contains("fail"), false);
}

/**
 * isValid_test
 */
void
JsonItem_Test::isValid_test()
{
    JsonItem emptyItem;
    UNITTEST(emptyItem.isValid(), false);
    JsonItem testItem = getTestItem();
    UNITTEST(testItem.isValid(), true);
}

/**
 * isObject_isArray_isValue_test
 */
void
JsonItem_Test::isObject_isArray_isValue_test()
{
    std::map<std::string, JsonItem> emptyMap;
    JsonItem objectItem(emptyMap);
    UNITTEST(objectItem.isObject(), true);

    std::vector<JsonItem> emptyArray;
    JsonItem arrayItem(emptyArray);
    UNITTEST(arrayItem.isArray(), true);

    JsonItem stringItem("test");
    UNITTEST(stringItem.isValue(), true);
}

/**
 * remove_test
 */
void
JsonItem_Test::remove_test()
{
    JsonItem testItem = getTestItem();

    UNITTEST(testItem.remove("item"), true);
    UNITTEST(testItem.remove("item"), false);
    UNITTEST(testItem.getSize(), 2);
}

/**
 * @brief JsonItem_Test::getTestItem
 * @return
 */
JsonItem
JsonItem_Test::getTestItem()
{
    std::string input("{\n"
                      "    \"item\": {\n"
                      "        \"sub_item\": \"test_value\"\n"
                      "    },\n"
                      "    \"item2\": {\n"
                      "        \"sub_item2\": \"something\"\n"
                      "    },\n"
                      "    \"loop\": [\n"
                      "        {\n"
                      "            \"x\": 42\n"
                      "        },\n"
                      "        {\n"
                      "            \"x\": 42.000000\n"
                      "        },\n"
                      "        1234,\n"
                      "        {\n"
                      "            \"x\": -42.000000\n"
                      "        }\n"
                      "    ]\n"
                      "}");

    JsonItem output;
    output.parse(input);

    return output;
}

}  // namespace Json
}  // namespace Kitsune
