/**
 *  @file    jsonObjectTest.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONOBJECTTEST_H
#define JSONOBJECTTEST_H

#include <commonTest.h>

namespace Kitsune
{
namespace Json
{

class JsonObjectTest: public Kitsune::CommonTest
{
public:
    JsonObjectTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void removeTestCase();
    void cleanupTestCase();
};

}
}

#endif // JSONOBJECTTEST_H
