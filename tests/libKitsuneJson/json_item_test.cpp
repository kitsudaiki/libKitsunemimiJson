/**
 *  @file    jsonItem_test.cpp
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#include "json_item_test.h"
#include <common_items/data_items.h>

namespace Kitsune
{
namespace Json
{

JsonItem_Test::JsonItem_Test()
    : Kitsune::Common::UnitTest("JsonItem_Test")
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
 * @brief constructor_test
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
 * @brief assigmentOperator_test
 */
void
JsonItem_Test::assigmentOperator_test()
{
    JsonItem testItem = getTestItem();

    JsonItem copy;
    copy = testItem;

    UNITTEST(copy.toString(), testItem.toString());
}

/**
 * @brief setValue_test
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
 * @brief insert_test
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
 * @brief append_test
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
 * @brief replaceItem_test
 */
void
JsonItem_Test::replaceItem_test()
{
    JsonItem testItem;
    testItem.append(JsonItem(42));
    testItem.append(JsonItem("42"));
    UNITTEST(testItem[0].toString(), "42");
    UNITTEST(testItem.replaceItem(0, JsonItem("ok")), true);
    UNITTEST(testItem[0].toString(), "ok");

    // negative test
    UNITTEST(testItem.replaceItem(10, JsonItem("fail")), false);
    UNITTEST(testItem.replaceItem(0, JsonItem()), false);
}

/**
 * @brief getItemContent_test
 */
void
JsonItem_Test::getItemContent_test()
{
    JsonItem testItem = getTestItem();
    Common::DataItem* itemPtr = testItem.getItemContent();

    UNITTEST(itemPtr->toString(true), testItem.toString(true));
}

/**
 * @brief get_test
 */
void
JsonItem_Test::get_test()
{
    JsonItem testItem = getTestItem();
    UNITTEST(testItem["loop"][0]["x"].toString(), "42");
    UNITTEST(testItem.get("loop").get(0).get("x").toString(), "42");
    UNITTEST(testItem.get("loop").get(0).get("x").setValue("43"), true);
    UNITTEST(testItem.get("loop").get(0).get("x").toString(), "43");
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

    // string-value
    UNITTEST(stringValue.getString(), "test");
    UNITTEST(stringValue.getInt(), 0);
    UNITTEST(stringValue.getFloat(), 0.0f);

    // int-value
    UNITTEST(intValue.getString(), "");
    UNITTEST(intValue.getInt(), 42);
    UNITTEST(intValue.getFloat(), 0.0f);

    // float-value
    UNITTEST(floatValue.getString(), "");
    UNITTEST(floatValue.getInt(), 0);
    UNITTEST(floatValue.getFloat(), 42.5f);
}

/**
 * @brief getSize_test
 */
void
JsonItem_Test::getSize_test()
{
    JsonItem testItem = getTestItem();
    UNITTEST(testItem.getSize(), 3);
}

/**
 * @brief getKeys_test
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
 * @brief contains_test
 */
void
JsonItem_Test::contains_test()
{
    JsonItem testItem = getTestItem();
    UNITTEST(testItem.contains("item"), true);
    UNITTEST(testItem.contains("fail"), false);
}

/**
 * @brief isValid_test
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
 * @brief isObject_isArray_isValue_test
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
 * @brief remove_test
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
}  // namespace Kitsune
