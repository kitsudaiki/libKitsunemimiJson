/**
 *  @file    static_parseString_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef STATIC_PARSESTRING_TEST_HPP
#define STATIC_PARSESTRING_TEST_HPP

#include <testing/commonTest.hpp>

namespace Kitsune
{
namespace Json
{
class Static_ParseString_Test : public Kitsune::CommonTest
{
public:
    Static_ParseString_Test();

private:
    void parserPositiveTest();
    void parserNegativeTest();
};

}  // namespace Json
}  // namespace Kitsune

#endif // STATIC_PARSESTRING_TEST_HPP
