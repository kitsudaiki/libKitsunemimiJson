/**
 *  @file    jsonValueObjectsTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONVSLUROBJECTTEST_H
#define JSONVSLUROBJECTTEST_H

#include <testing/commonTest.h>

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
    void cleanupTestCase();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONVSLUROBJECTTEST_H
