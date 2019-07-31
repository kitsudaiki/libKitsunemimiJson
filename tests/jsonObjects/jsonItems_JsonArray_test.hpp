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
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void removeTestCase();
    void cleanupTestCase();

    JsonArray* m_array = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEMS_JSONARRAY_TEST_HPP
