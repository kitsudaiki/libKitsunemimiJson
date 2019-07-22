/**
 *  @file    main.cpp
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 *
 *  MIT License
 */

#include <iostream>
#include <jsonObjects/jsonArrayObjectsTest.h>
#include <jsonObjects/jsonValueObjectsTest.h>
#include <jsonObjects/jsonObjectObjectsTest.h>
#include <parsingTest.h>

int main()
{
    Kitsune::Json::ParsingTest();

    Kitsune::Json::JsonValueObjectsTest();
    Kitsune::Json::JsonArrayObjectsTest();
    Kitsune::Json::JsonObjectObjectsTest();
}
