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

#include <testing/unit_test.h>
#include <json_item.h>

namespace Kitsune
{
namespace Json
{
class JsonItem_Test
        : public Kitsune::Common::UnitTest
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

    void getSize_test();
    void getKeys_test();
    void contains_test();

    void isValid_test();
    void isNull_test();
    void isObject_isArray_isValue_test();

    void remove_test();

    JsonItem getTestItem();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEM_TEST_H
