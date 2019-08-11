/**
 *  @file    jsonItems_parseString_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSONITEMS_PARSESTRING_TEST_HPP
#define JSONITEMS_PARSESTRING_TEST_HPP

#include <testing/test.hpp>

namespace Kitsune
{
namespace Json
{
class JsonItems_ParseString_Test
        : public Kitsune::Common::Test
{
public:
    JsonItems_ParseString_Test();

private:
    void parseString_test();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSONITEMS_PARSESTRING_TEST_HPP
