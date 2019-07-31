/**
 *  @file    jsonItems_JsonArray_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONITEMS_JSONARRAY_TEST_HPP
#define JSONITEMS_JSONARRAY_TEST_HPP

#include <testing/commonTest.hpp>

namespace Kitsune
{
namespace Json
{
class JsonArray;

class JsonItems_JsonArray_Test : public Kitsune::CommonTest
{
public:
    JsonItems_JsonArray_Test();

private:
    void parseString_test();
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

    void append_test();

    JsonArray initTestArray();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEMS_JSONARRAY_TEST_HPP
