/**
 *  @file    jsonValueObjectsTest.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef JSONVSLUROBJECTTEST_H
#define JSONVSLUROBJECTTEST_H

#include <commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonValue;

class JsonValueObjectsTest: public Kitsune::CommonTest
{
public:
    JsonValueObjectsTest();
private:
    void initTestCase();
    void insertTestCase();
    void getTestCase();
    void cleanupTestCase();

    JsonValue* m_valueString = nullptr;
    JsonValue* m_valueInt = nullptr;
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONVSLUROBJECTTEST_H
