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
#include <parsingTest.h>

int main()
{
    Kitsune::Json::ParsingTest();

    Kitsune::Json::JsonValueObjectsTest();
    Kitsune::Json::JsonItems_JsonArray_Test();
    Kitsune::Json::JsonObjectObjectsTest();
}
