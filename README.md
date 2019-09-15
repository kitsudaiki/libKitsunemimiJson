# libKitsuneJson

## Description

This library provides the functionality to parse and handle the content of json-files. 

## Common Information aboud my projects

Here some common information about my projects and my code-styling. It's not complete and a bit short. I will write a styling-guide for my projects, where I will write this a bit longer with more explanation, why I make it like this.

### About my kitsune libraries

1. All my libraries beginning with `libKitsune`, because I needed a naming to identify my own libraries and I decided to use `Kitsune` as name, because Kitsunemimi are moe. ;)

2. The namespace of the code within the libraries is identically to the name of the library. So for example all content of `libKitsuneCommon` has the namespace `Kitsune::Common`.

3. If you only want to use the library, beside the binary you only ne the public methods and variables in the header-files, which are located in the `include`-directory of each `libKitsune`-repo. I try my best to make these as small and self-explaining, as possible. 

### About my repositories in general

1. All my projects are mirrored to gitlab, where I have still my gitlab-ci runner.

2. In each project-repository is an `build.sh`-script to make it easier for you to build the project by yourself. It download and link all required git-repositories in the correct version and link it all. This script is also used by the gitlab-ci-runner and so it is everytime up-to-date.

3. All my projects have unit-tests, which are executed by the ci-runner in each commit. Most of the functions are tested. Primary some negative-tests are missing. I try to avoid mocks in the tests as much as possible. Even tcp-socket-tests using the localhost for real data-transfer-tests.

4. For the naming of variables, methods and classes, I use camel case and for the names of files and directories, I use snake case.

5. About my comments:

	- Many comments in my code seems to be a bit useless, but I like to use them for optical separation. I also write them, when I think I finished the programming task and while writing the comments I recheck the code under the comment again and often I find improvements or bugs while this.

	- At first I planned to use doxygen comment-style for methods and files, but I think I will change this, because while writing the current state of the code, I don't like it to write big comments for each simple self-explaining method.

	- I don't like it to write much comments into header-files. More exactly I absolutly hate it, when I have to search the provided functions of a header between a massive amount of comments. Header-files are for me primary to have an overview of all provided functions, which I want to see as fast as possible. Comments of functions, parameters and return-values in my code are only written into the source-files. So when something is unclear for a specific method, then look into the source-file. If the comment there are not helpful for you, then please write me a mail or an issue to fix this. 

6. I try to avoid templates and macros as much as possible. I don't dislike them, but I only use them, when I don't have another solution. 


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
