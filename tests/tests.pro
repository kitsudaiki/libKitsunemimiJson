include(../defaults.pri)

QT -= qt core gui

CONFIG -= app_bundle
CONFIG += c++14 console


LIBS += -L../../libKitsuneCommon/src -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/src/debug -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/src/release -lKitsuneCommon
INCLUDEPATH += ../../libKitsuneCommon/include/libKitsuneCommon


INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneJson

SOURCES += \
        main.cpp \
    jsonObjects/jsonItems_JsonArray_test.cpp \
    jsonObjects/jsonItems_JsonObject_test.cpp \
    jsonObjects/jsonItems_JsonValue_test.cpp \
    static_parseString_test.cpp

HEADERS += \
    jsonObjects/jsonItems_JsonArray_test.hpp \
    jsonObjects/jsonItems_JsonObject_test.hpp \
    jsonObjects/jsonItems_JsonValue_test.hpp \
    static_parseString_test.h

