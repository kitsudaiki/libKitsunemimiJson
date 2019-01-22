/**
 *  @file    jsonValueItemTest.h
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
class JsonItem;

class JsonValueItemTest: public Kitsune::CommonTest
{
public:
    JsonValueItemTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void cleanupTestCase();

    JsonItem* m_valueString = nullptr;
    JsonItem* m_valueInt = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONVSLURTEST_H
