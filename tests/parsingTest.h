/**
 *  @file    parsingTest.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <../../../LibKitsuneCommon/include/libKitsuneCommon/commonTest.h>

namespace Kitsune
{
namespace Json
{
class ParsingTest: public Kitsune::CommonTest
{
public:
    ParsingTest();

private:
    void initTestCase();
    void parserPositiveTest();
    void parserNegativeTest();
    void cleanupTestCase();
};

}  // namespace Json
}  // namespace Kitsune

#endif // PARSERTEST_H
