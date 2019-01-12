/**
 *  @file    main.cpp
 *  @version 0.1.0
 *
 *  @author  Tobias Anker
 *  Contact: tobias.anker@kitsunemimi.moe
 */

#include <iostream>
#include <jsonArrayTest.h>
#include <jsonValueTest.h>
#include <jsonObjectTest.h>
#include <parsingTest.h>

int main(int argc, char *argv[])
{
    Kitsune::Json::ParsingTest();
    Kitsune::Json::JsonValueTest();
    Kitsune::Json::JsonArrayTest();
    Kitsune::Json::JsonObjectTest();
}
