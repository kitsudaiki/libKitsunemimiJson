/**
 *  @file    jsonObjectObjectsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONOBJECTOBJECTTEST_H
#define JSONOBJECTOBJECTTEST_H

#include <testing/commonTest.h>

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
    void cleanupTestCase();

};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECTOBJECTTEST_H
