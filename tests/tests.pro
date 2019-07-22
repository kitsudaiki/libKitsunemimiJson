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
    parsingTest.cpp \
    jsonObjects/jsonArrayObjectsTest.cpp \
    jsonObjects/jsonObjectObjectsTest.cpp \
    jsonObjects/jsonValueObjectsTest.cpp

HEADERS += \
    parsingTest.h \
    jsonObjects/jsonArrayObjectsTest.h \
    jsonObjects/jsonObjectObjectsTest.h \
    jsonObjects/jsonValueObjectsTest.h

