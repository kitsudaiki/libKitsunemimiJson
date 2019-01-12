/**
 *  @file    parsingTest.h
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <commonTest.h>

namespace Kitsune
{
namespace Json
{
class JsonParserInterface;

class ParsingTest: public Kitsune::CommonTest
{
public:
    ParsingTest();

private:
    void initTestCase();
    void parserPositiveTest();
    void parserNegativeTest();
    void cleanupTestCase();

    JsonParserInterface* m_parser = nullptr;
};

}
}

#endif // PARSERTEST_H
