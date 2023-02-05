# libKitsunemimiJson

## IMPORTANT: This repository is no longer maintained, because in context of issue https://github.com/kitsudaiki/Hanami-AI/issues/31 the content was moved into the main-repository (https://github.com/kitsudaiki/Hanami-AI).

![Github workfloat status](https://img.shields.io/github/actions/workflow/status/kitsudaiki/libKitsunemimiJson/build_test.yml?branch=develop&style=flat-square&label=build%20and%20test)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/kitsudaiki/libKitsunemimiJson?label=version&style=flat-square)
![GitHub](https://img.shields.io/github/license/kitsudaiki/libKitsunemimiJson?style=flat-square)
![C++Version](https://img.shields.io/badge/c%2B%2B-17-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux--x64-lightgrey?style=flat-square)

## Description

This library provides the functionality to parse and handle the content of json-files. 

## Build

### Requirements

name | repository | version | task
--- | --- | --- | ---
g++ | g++ | >= 8.0 | Compiler for the C++ code.
make | make | >= 4.0 | process the make-file, which is created by qmake to build the programm with g++
qmake | qt5-qmake | >= 5.0 | This package provides the tool qmake, which is similar to cmake and create the make-file for compilation.
FLEX | flex | >= 2.6 | Build the lexer-code for all used parser.
GNU Bison | bison | 3.x | Build the parser-code together with the lexer-code.

Installation on Ubuntu/Debian:

```bash
sudo apt-get install g++ make qt5-qmake flex bison
```

IMPORTANT: All my projects are only tested on Linux. 

### Kitsunemimi-repositories

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsunemimiCommon | develop |  https://github.com/kitsudaiki/libKitsunemimiCommon.git

HINT: These Kitsunemimi-Libraries will be downloaded and build automatically with the build-script below.

### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.


Run the following commands:

```
git clone https://github.com/kitsudaiki/libKitsunemimiJson.git
cd libKitsunemimiJson
./build.sh
cd ../result
```

It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.


## Usage

**Header-file:** `libKitsunemimiJson/json_item.h`

The `JsonItem`-class is the handler for the json-file-content. The functions in the header should be really self-explaned, if something is unclear, see the following basic-example or the comments in the cpp-file.

```cpp
#include <libKitsunemimiJson/json_item.h>
#include <libKitsunemimiCommon/logger.h>

// short test-string for demonstration. 
const std::string testString(
                "{\n"
                "    \"item\": {\n"
                "        \"sub_item\": \"test_value\"\n"
                "    },\n"
                "    \"item2\": {\n"
                "        \"sub_item2\": \"something\"\n"
                "    },\n"
                "    \"loop\": [\n"
                "        {\n"
                "            \"x\": 42\n"
                "        },\n"
                "        {\n"
                "            \"x\": 42.000000\n"
                "        },\n"
                "        1234,\n"
                "        {\n"
                "            \"x\": -42.000000,\n"
                "            \"y\": true,\n"
                "            \"z\": null\n"
                "        }\n"
                "    ]\n"
                "}");



Kitsunemimi::JsonItem object;

// parse the test-string
Kitsunemimi::ErrorContainer error;
bool result = object.parse(testString, error);
// if result is true, then paring was successful
// else, error contains the error-message of the parser and can be printed with LOG_ERROR(error);


// get value
std::string value = object.get("loop").get(0).get("x").toString()
// value would contain 42 as string
// or with []-operator
value = testItem["loop"][0]["x"].toString();


// set-value
object.get("loop").get(0).get("x").setValue(1337);


// convert back into an json-file-string
std::string output = object.toString();
// output-variable would contain the same like the inital parsed testString
// but with some additional double quotes at the strin-values and maybe another 
// order of the groups and keys inside the groups and the replaced value
```

This is only a basic example. There are many more methods like insert, append, remove, etc.


IMPORTANT: The get-function has a beside the value a second argument. This is a bool-value, which says, if the get should return a copy or only a linked version. This is per default false, to `get` returns per default only a linked version for faster access. With this its possible to set values like in the example. If the original object is deleted, all with get returned linked versions become unusable. You can also do `get("value", true)` to get a fully copied version. 

IMPORTANT: The `[]`-operator is the same like get with true-flag and returns every time a copy version. So its slow and can not change values inside the tree. Be aware of this.


## Contributing

Please give me as many inputs as possible: Bugs, bad code style, bad documentation and so on.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
