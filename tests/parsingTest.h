/**
 *  @file    parsingTest.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <testing/commonTest.h>

namespace Kitsune
{
namespace Json
{
class ParsingTest : public Kitsune::CommonTest
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
