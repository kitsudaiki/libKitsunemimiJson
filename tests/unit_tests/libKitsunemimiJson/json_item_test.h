/**
 *  @file    jsonItem_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef JSONITEM_TEST_H
#define JSONITEM_TEST_H

#include <assert.h>

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>
#include <libKitsunemimiJson/json_item.h>

namespace Kitsunemimi
{
class JsonItem_Test
        : public Kitsunemimi::CompareTestHelper
{
public:
    JsonItem_Test();

private:
    void constructor_test();
    void assigmentOperator_test();
    void setValue_test();
    void insert_test();
    void append_test();
    void replaceItem_test();
    void deleteContent_test();

    void getItemContent_test();
    void get_test();
    void getString_getInt_getFloat_test();

    void size_test();
    void getKeys_test();
    void contains_test();

    void isValid_test();
    void isNull_test();
    void isMap_isArray_isValue_test();
    void isString_isInteger_isFloat_isBool_test();

    void remove_test();

    JsonItem getTestItem();
};

}  // namespace Kitsunemimi

#endif // JSONITEM_TEST_H
