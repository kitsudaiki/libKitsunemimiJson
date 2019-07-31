/**
 *  @file    jsonItems_JsonObject_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONITEMS_JSONOBJECT_TEST_HPP
#define JSONITEMS_JSONOBJECT_TEST_HPP

#include <testing/commonTest.hpp>

namespace Kitsune
{
namespace Json
{
class JsonObject;

class JsonItems_JsonObject_Test : public Kitsune::CommonTest
{
public:
    JsonItems_JsonObject_Test();

private:
    void operator_test();
    void get_test();
    void getSize_test();
    void remove_test();
    void copy_test();
    void print_test();
    void getType_test();
    void isValue_isObject_isArray_test();
    void toValue_toObject_toArray_test();
    void toString_toInt_toFloat_test();

    void insert_test();
    void getString_getInt_getFloat_test();
    void getKeys_test();
    void getValues_test();
    void contains_test();

    JsonObject initTestObject();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEMS_JSONOBJECT_TEST_HPP
