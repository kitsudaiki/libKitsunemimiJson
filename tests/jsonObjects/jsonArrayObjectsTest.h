/**
 *  @file    jsonArrayObjectsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONARRAYOBJECTTEST_H
#define JSONARRAYOBJECTTEST_H

#include <testing/commonTest.h>

namespace Kitsune
{
namespace Json
{

class JsonArrayObjectsTest: public Kitsune::CommonTest
{
public:
    JsonArrayObjectsTest();
private:
    void initTestCase();
    void insertTestCase();
    void cleanupTestCase();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONARRAYOBJECTTEST_H
