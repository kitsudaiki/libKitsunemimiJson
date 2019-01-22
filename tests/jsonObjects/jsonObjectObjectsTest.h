/**
 *  @file    jsonObjectObjectsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONOBJECTOBJECTTEST_H
#define JSONOBJECTOBJECTTEST_H

#include <commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonObject;

class JsonObjectObjectsTest: public Kitsune::CommonTest
{
public:
    JsonObjectObjectsTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void removeTestCase();
    void cleanupTestCase();

    JsonObject* m_object = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECTOBJECTTEST_H
