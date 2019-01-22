/**
 *  @file    jsonObjectItemTest.h
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
class JsonObject;
class JsonItem;

class JsonObjectItemTest: public Kitsune::CommonTest
{
public:
    JsonObjectItemTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void removeTestCase();
    void cleanupTestCase();

    JsonItem* m_item = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONOBJECTTEST_H
