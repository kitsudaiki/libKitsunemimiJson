/**
 *  @file    main.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include <iostream>
#include <jsonItem/jsonArrayItemTest.h>
#include <jsonItem/jsonValueItemTest.h>
#include <jsonItem/jsonObjectItemTest.h>
#include <jsonObjects/jsonArrayObjectsTest.h>
#include <jsonObjects/jsonValueObjectsTest.h>
#include <jsonObjects/jsonObjectObjectsTest.h>
#include <parsingTest.h>

int main()
{
    Kitsune::Json::ParsingTest();

    Kitsune::Json::JsonValueItemTest();
    Kitsune::Json::JsonArrayItemTest();
    Kitsune::Json::JsonObjectItemTest();

    Kitsune::Json::JsonValueObjectsTest();
    Kitsune::Json::JsonArrayObjectsTest();
    Kitsune::Json::JsonObjectObjectsTest();
}
