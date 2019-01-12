#include <json_parsing/jsonParserInterface.h>
#include <jsonObjects.h>
#include <iostream>

int main(int argc, char *argv[])
{
    std::string input("{\"item\": "
                   "{ \"sub_item\": \"test_value\"},"
               "\"item2\": "
                   "{ \"sub_item2\": \"something\"},"
               "\"loop\": "
                   "[ {\"x\" :\"test1\" }, {\"x\" :\"test2\" }, {\"x\" :\"test3\" }]"
               "}");

    std::cout<<"input_string: "<<input<<std::endl;

    Kitsune::Json::JsonParserInterface parser(false);
    bool ret = parser.parse(input);

    if(ret == false) {
        std::cout<<"fail"<<std::endl;
    } else {
        std::cout<<"YEAH"<<std::endl;
    }

    Kitsune::Json::JsonObject* output = parser.getOutput();

    std::string outputString = "";
    output->print(&outputString);
    std::cout<<"output-string: "<<outputString<<std::endl;
}
