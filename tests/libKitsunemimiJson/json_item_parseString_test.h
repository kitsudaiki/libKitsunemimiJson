/**
 *  @file    jsonItems_parseString_test.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 */

#ifndef JSON_ITEM_PARSESTRING_TEST_H
#define JSON_ITEM_PARSESTRING_TEST_H

#include <libKitsunemimiCommon/test.h>

namespace Kitsunemimi
{
namespace Json
{
class JsonItem_ParseString_Test
        : public Kitsunemimi::Common::Test
{
public:
    JsonItem_ParseString_Test();

private:
    void parseString_test();
};

}  // namespace Json
}  // namespace Kitsunemimi

#endif // JSON_ITEM_PARSESTRING_TEST_H
