/**
 *  @file    jsonArrayItemTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONARRAYTEST_H
#define JSONARRAYTEST_H

#include <testing/commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonArray;
class JsonItem;

class JsonArrayItemTest: public Kitsune::CommonTest
{
public:
    JsonArrayItemTest();
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

#endif // JSONARRAYTEST_H
