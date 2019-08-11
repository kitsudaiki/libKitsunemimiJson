/**
 *  @file    jsonItem_test.hpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONITEM_TEST_HPP
#define JSONITEM_TEST_HPP

#include <testing/test.hpp>
#include <jsonItem.hpp>

namespace Kitsune
{
namespace Json
{
class JsonItem_Test
        : public Kitsune::Common::Test
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

    void getItemContent_test();
    void get_test();
    void getString_getInt_getFloat_test();

    void getSize_test();
    void getKeys_test();
    void contains_test();

    void isValid_test();
    void isObject_isArray_isValue_test();

    void remove_test();

    JsonItem getTestItem();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEM_TEST_HPP
