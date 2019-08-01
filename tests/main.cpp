/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>
#include <libKitsuneJson/jsonItems_JsonArray_test.hpp>
#include <libKitsuneJson/jsonItems_JsonValue_test.hpp>
#include <libKitsuneJson/jsonItems_JsonObject_test.hpp>
#include <libKitsuneJson/jsonItems_parseString_test.h>

int main()
{
    Kitsune::Json::JsonItems_ParseString_Test();

    Kitsune::Json::JsonItems_JsonValue_Test();
    Kitsune::Json::JsonItems_JsonArray_Test();
    Kitsune::Json::JsonItems_JsonObject_Test();
}
