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
    parsing_test.cpp \
    jsonObjects/jsonItems_JsonArray_test.cpp \
    jsonObjects/jsonItems_JsonObject_test.cpp \
    jsonObjects/jsonItems_JsonValue_test.cpp

HEADERS += \
    parsingTest.h \
    jsonObjects/jsonItems_JsonArray_test.hpp \
    jsonObjects/jsonItems_JsonObject_test.hpp \
    jsonObjects/jsonItems_JsonValue_test.hpp

