/**
 *  @file    jsonValueTest.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONVSLURTEST_H
#define JSONVSLURTEST_H

#include <commonTest.h>

namespace Kitsune
{
namespace Json
{

class JsonValueTest: public Kitsune::CommonTest
{
public:
    JsonValueTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void removeTestCase();
    void cleanupTestCase();
};

}
}

#endif // JSONVSLURTEST_H
