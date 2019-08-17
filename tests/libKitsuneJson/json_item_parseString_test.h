/**
 *  @file    jsonItems_parseString_test.h
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#ifndef JSON_ITEM_PARSESTRING_TEST_H
#define JSON_ITEM_PARSESTRING_TEST_H

#include <testing/test.h>

namespace Kitsune
{
namespace Json
{
class JsonItem_ParseString_Test
        : public Kitsune::Common::Test
{
public:
    JsonItem_ParseString_Test();

private:
    void parseString_test();
};

}  // namespace Json
}  // namespace Kitsune

#endif // JSON_ITEM_PARSESTRING_TEST_H
