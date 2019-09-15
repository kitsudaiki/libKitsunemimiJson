# libKitsuneJson

## Description

This library provides the functionality to parse and handle the content of json-files. 

### About my kitsune libraries

My first libraries hab really common names like libCommon and so on, but I thought this could be hard to find my code between other libraries, when my projects will become bigger. So I decided to make a common name over all my libraries, similar to the boost-libraries, for a better handling. I decided to use `Kitsune` as name for my projects, because Kitsunemimi are moe. ;)

### About my repositories in general

At the moment there are over 10 Kitsune-libraries an multiple tools in my private repos. I plan to make all open-source, but I have much to learn about open-source-projects. Most of all I have to improve my ticket-handling. So please help me to improve my workflow.

All my projects are mirrored to gitlab, where I have still my gitlab-ci runner. 

I don't really like it to write much comments into header-files. More exactly I absolutly hate it, when I have to search the provided functions of a header between a massive amount of comments. Header-files are for me primary to have an overview, of all provided functions, which I have see as fast as possible. Comments of functions, parameters and return-values in my code are only written into the source-file. So when something is unclear for a specific method, than look into the source-file. If the comment there are not helpful for you, then please write me a mail or an issue to fix this. 

## Build

### Requirements

paket | version
--- | ---
g++ | 6.3.0
qt5-qmake | 5.7.1
bison | 3.0.4
flex | 2.6.1 

This are the version I have installed under Debian Stable via apt. Some older or newer version should work as well. I write my projects with the Qt-creator, but without Qt itself. Thats why qmake is required to build my projects.

IMPORTANT: All my projects are only tested on Linux. 

#### Kitsune-repositories

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsuneCommon | 0.5.2 |  https://github.com/tobiasanker/libKitsuneCommon.git


### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.

Before running the build-script:

```bash
.
└── libKitsuneJson
    ├── build.sh
    └── ...
```

After running the build-script:

```bash
.
└── libKitsuneJson
    ├── build.sh
    └── ...
```

After running the build-script:

```bash
.
├── build
│   ├── libKitsuneCommon
│   │   └── ...
│   └── libKitsuneJson
│       └── ...
│
├── libKitsuneCommon
│   └── ...
├── libKitsuneJson
│   ├── build.sh
│   └── ...
│
└── result
    ├── include
    │   ├── libKitsuneCommon
    │   │   └── ...
    │   └── libKitsuneJson
    │       └── ...
    │
    ├── libKitsuneCommon.so -> libKitsuneCommon.so.0.5.2
    ├── libKitsuneCommon.so.0 -> libKitsuneCommon.so.0.5.2
    ├── libKitsuneCommon.so.0.5 -> libKitsuneCommon.so.0.5.2
    ├── libKitsuneCommon.so.0.5.2
    │
    ├── libKitsuneJson.so -> libKitsuneJson.so.0.4.0
    ├── libKitsuneJson.so.0 -> libKitsuneJson.so.0.4.0
    ├── libKitsuneJson.so.0.4 -> libKitsuneJson.so.0.4.0
    └── libKitsuneJson.so.0.4.0
```


It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.


## Usage

**Header-file:** `json_item.h`

The `JsonItem`-class is the handler for the json-file-content. The functions in the header should be really self-explaned, if something is unclear, see the following basic-example or the comments in the cpp-file.

```cpp
#include <json_item.h>

// short test-string for demonstration. 
const std::string testString(
                "{\n"
                "    item: {\n"
                "        sub_item: \"test_value\"\n"
                "    },\n"
                "    item2: {\n"
                "        sub_item2: \"something\"\n"
                "    },\n"
                "    loop: [\n"
                "        {\n"
                "            x: 42\n"
                "        },\n"
                "        {\n"
                "            x: 42.000000\n"
                "        },\n"
                "        1234,\n"
                "        {\n"
                "            x: -42.000000\n"
                "        }\n"
                "    ]\n"
                "}");



JsonItem object;

// parse the test-string
std::pair<bool, std::string> result = object.parse(testString);
// if result.first is true, then paring was successful
// else, result.second contains the error-message of the parser


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
