/**
 *  @file    jsonItem_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "json_item_test.h"
#include <libKitsunemimiCommon/common_items/data_items.h>

namespace Kitsunemimi
{
namespace Json
{

JsonItem_Test::JsonItem_Test()
    : Kitsunemimi::Common::Test("JsonItem_Test")
{
    constructor_test();
    assigmentOperator_test();
    setValue_test();
    insert_test();
    append_test();
    replaceItem_test();
    replaceItem_test();

    getItemContent_test();
    get_test();
    getString_getInt_getFloat_test();

    getSize_test();
    getKeys_test();
    contains_test();

    isValid_test();
    isNull_test();
    isObject_isArray_isValue_test();

    remove_test();
}

/**
 * @brief constructor_test
 */
void
JsonItem_Test::constructor_test()
{
    JsonItem emptyItem;
    TEST_EQUAL(emptyItem.isValid(), false);

    std::map<std::string, JsonItem> emptyMap;
    JsonItem objectItem(emptyMap);
    TEST_EQUAL(objectItem.isObject(), true);

    JsonItem objectCopyItem(objectItem);
    TEST_EQUAL(objectCopyItem.isObject(), true);

    std::vector<JsonItem> emptyArray;
    JsonItem arrayItem(emptyArray);
    TEST_EQUAL(arrayItem.isArray(), true);

    JsonItem stringItem("test");
    TEST_EQUAL(stringItem.isValue(), true);

    JsonItem intItem(42);
    TEST_EQUAL(intItem.isValue(), true);

    JsonItem floatItem(42.0f);
    TEST_EQUAL(floatItem.isValue(), true);

    JsonItem boolItem(true);
    TEST_EQUAL(boolItem.isValue(), true);
}

/**
 * @brief assigmentOperator_test
 */
void
JsonItem_Test::assigmentOperator_test()
{
    JsonItem testItem = getTestItem();

    JsonItem copy;
    copy = testItem;

    TEST_EQUAL(copy.toString(), testItem.toString());
}

/**
 * @brief setValue_test
 */
void
JsonItem_Test::setValue_test()
{
    JsonItem testItem;
    TEST_EQUAL(testItem.setValue("test"), true);
    TEST_EQUAL(testItem.setValue(42), true);
    TEST_EQUAL(testItem.setValue(42.0f), true);
    TEST_EQUAL(testItem.setValue(true), true);

    TEST_EQUAL(testItem.isValid(), true);


    // negative test
    std::map<std::string, JsonItem> emptyMap;
    JsonItem objectItem(emptyMap);
    TEST_EQUAL(objectItem.setValue("test"), false);
}

/**
 * @brief insert_test
 */
void
JsonItem_Test::insert_test()
{
    JsonItem testItem;
    TEST_EQUAL(testItem.insert("key", JsonItem(42)), true);
    TEST_EQUAL(testItem.insert("key", JsonItem("24"), true), true);
    TEST_EQUAL(testItem["key"].getString(), "24");
    TEST_EQUAL(testItem.isObject(), true);

    // negative test
    TEST_EQUAL(testItem.insert("key", JsonItem(43)), false);
    TEST_EQUAL(testItem.insert("fail", JsonItem()), false);
}

/**
 * @brief append_test
 */
void
JsonItem_Test::append_test()
{
    JsonItem testItem;
    TEST_EQUAL(testItem.append(JsonItem(42)), true);
    TEST_EQUAL(testItem.isArray(), true);
    TEST_EQUAL(testItem[0].getInt(), 42);

    // negative test
    TEST_EQUAL(testItem.append(JsonItem()), false);
}

/**
 * @brief replaceItem_test
 */
void
JsonItem_Test::replaceItem_test()
{
    JsonItem testItem;
    testItem.append(JsonItem(42));
    testItem.append(JsonItem("42"));
    TEST_EQUAL(testItem[0].toString(), "42");
    TEST_EQUAL(testItem.replaceItem(0, JsonItem("ok")), true);
    TEST_EQUAL(testItem[0].toString(), "ok");

    // negative test
    TEST_EQUAL(testItem.replaceItem(10, JsonItem("fail")), false);
    TEST_EQUAL(testItem.replaceItem(0, JsonItem()), false);
}

/**
 * @brief deleteContent_test
 */
void
JsonItem_Test::deleteContent_test()
{
    JsonItem testItem;
    testItem.append(JsonItem(42));
    testItem.append(JsonItem("42"));
    TEST_EQUAL(testItem.isNull(), false);
    TEST_EQUAL(testItem.deleteContent(), true);
    TEST_EQUAL(testItem.deleteContent(), false);
    TEST_EQUAL(testItem.isNull(), true);
}

/**
 * @brief getItemContent_test
 */
void
JsonItem_Test::getItemContent_test()
{
    JsonItem testItem = getTestItem();
    Common::DataItem* itemPtr = testItem.getItemContent();

    TEST_EQUAL(itemPtr->toString(true), testItem.toString(true));
}

/**
 * @brief get_test
 */
void
JsonItem_Test::get_test()
{
    JsonItem testItem = getTestItem();
    TEST_EQUAL(testItem["loop"][0]["x"].toString(), "42");
    TEST_EQUAL(testItem.get("loop").get(0).get("x").toString(), "42");
    TEST_EQUAL(testItem.get("loop").get(0).get("x").setValue("43"), true);
    TEST_EQUAL(testItem.get("loop").get(0).get("x").toString(), "43");
}

/**
 * @brief getString_getInt_getFloat_test
 */
void
JsonItem_Test::getString_getInt_getFloat_test()
{
    JsonItem stringValue("test");
    JsonItem intValue(42);
    JsonItem floatValue(42.5f);
    JsonItem boolValue(true);

    // string-value
    TEST_EQUAL(stringValue.getString(), "test");
    TEST_EQUAL(stringValue.getInt(), 0);
    TEST_EQUAL(stringValue.getFloat(), 0.0f);
    TEST_EQUAL(stringValue.getBool(), false);

    // int-value
    TEST_EQUAL(intValue.getString(), "");
    TEST_EQUAL(intValue.getInt(), 42);
    TEST_EQUAL(intValue.getFloat(), 0.0f);
    TEST_EQUAL(intValue.getBool(), false);

    // float-value
    TEST_EQUAL(floatValue.getString(), "");
    TEST_EQUAL(floatValue.getInt(), 0);
    TEST_EQUAL(floatValue.getFloat(), 42.5f);
    TEST_EQUAL(floatValue.getBool(), false);

    // bool-value
    TEST_EQUAL(boolValue.getString(), "");
    TEST_EQUAL(boolValue.getInt(), 0);
    TEST_EQUAL(boolValue.getFloat(), 0.0f);
    TEST_EQUAL(boolValue.getBool(), true);
}

/**
 * @brief getSize_test
 */
void
JsonItem_Test::getSize_test()
{
    JsonItem testItem = getTestItem();
    TEST_EQUAL(testItem.getSize(), 3);
}

/**
 * @brief getKeys_test
 */
void
JsonItem_Test::getKeys_test()
{
    JsonItem testItem = getTestItem();
    std::vector<std::string> keys = testItem.getKeys();
    TEST_EQUAL(keys.size(), 3);
    TEST_EQUAL(keys.at(0), "item");
    TEST_EQUAL(keys.at(1), "item2");
    TEST_EQUAL(keys.at(2), "loop");
}

/**
 * @brief contains_test
 */
void
JsonItem_Test::contains_test()
{
    JsonItem testItem = getTestItem();
    TEST_EQUAL(testItem.contains("item"), true);
    TEST_EQUAL(testItem.contains("fail"), false);
}

/**
 * @brief isValid_test
 */
void
JsonItem_Test::isValid_test()
{
    JsonItem emptyItem;
    TEST_EQUAL(emptyItem.isValid(), false);
    JsonItem testItem = getTestItem();
    TEST_EQUAL(testItem.isValid(), true);
}

/**
 * @brief isNull_test
 */
void
JsonItem_Test::isNull_test()
{
    JsonItem emptyItem;
    TEST_EQUAL(emptyItem.isNull(), true);
    JsonItem testItem = getTestItem();
    TEST_EQUAL(testItem.isNull(), false);
}

/**
 * @brief isObject_isArray_isValue_test
 */
void
JsonItem_Test::isObject_isArray_isValue_test()
{
    std::map<std::string, JsonItem> emptyMap;
    JsonItem objectItem(emptyMap);
    TEST_EQUAL(objectItem.isObject(), true);

    std::vector<JsonItem> emptyArray;
    JsonItem arrayItem(emptyArray);
    TEST_EQUAL(arrayItem.isArray(), true);

    JsonItem stringItem("test");
    TEST_EQUAL(stringItem.isValue(), true);
}

/**
 * @brief remove_test
 */
void
JsonItem_Test::remove_test()
{
    JsonItem testItem = getTestItem();

    TEST_EQUAL(testItem.remove("item"), true);
    TEST_EQUAL(testItem.remove("item"), false);
    TEST_EQUAL(testItem.getSize(), 2);
}

/**
 * @brief get a item for tests
 *
 * @return json-item with test-content
 */
JsonItem
JsonItem_Test::getTestItem()
{
    std::string input("{\n"
                      "    item: {\n"
                      "        sub_item: \"test_value\"\n"
                      "    },\n"
                      "    item2: {\n"
                      "        sub_item2: \"something\"\n"
                      "    },\n"
                      "    loop: [\n"
                      "        {\n"
                      "            x: 42\n"
                      "        },\n"
                      "        {\n"
                      "            x: 42.000000\n"
                      "        },\n"
                      "        1234,\n"
                      "        {\n"
                      "            x: -42.000000\n"
                      "        }\n"
                      "    ]\n"
                      "}");

    JsonItem output;
    output.parse(input);

    assert(output.isValid());

    return output;
}

}  // namespace Json
}  // namespace Kitsunemimi
