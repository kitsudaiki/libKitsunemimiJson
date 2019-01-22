/**
 *  @file    jsonArrayObjectsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONARRAYOBJECTTEST_H
#define JSONARRAYOBJECTTEST_H

#include <commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonArray;

class JsonArrayObjectsTest: public Kitsune::CommonTest
{
public:
    JsonArrayObjectsTest();
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

#endif // JSONARRAYOBJECTTEST_H
