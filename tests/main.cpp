/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>
#include <jsonObjects/jsonItems_JsonArray_test.hpp>
#include <jsonObjects/jsonItems_JsonValue_test.hpp>
#include <jsonObjects/jsonItems_JsonObject_test.hpp>
#include <static_parseString_test.h>

int main()
{
    Kitsune::Json::Static_ParseString_Test();

    Kitsune::Json::JsonItems_JsonValue_Test();
    Kitsune::Json::JsonItems_JsonArray_Test();
    Kitsune::Json::JsonItems_JsonObject_Test();
}
