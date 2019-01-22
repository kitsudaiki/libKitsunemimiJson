include(../defaults.pri)

QT -= qt core gui

CONFIG -= app_bundle
CONFIG += c++14 console


LIBS += -L../../libKitsuneCommon -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/debug -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/release -lKitsuneCommon
INCLUDEPATH += ../../libKitsuneCommon/include/libKitsuneCommon


INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneJson

SOURCES += \
        main.cpp \
    parsingTest.cpp \
    jsonItem/jsonArrayItemTest.cpp \
    jsonItem/jsonObjectItemTest.cpp \
    jsonItem/jsonValueItemTest.cpp \
    jsonObjects/jsonArrayObjectsTest.cpp \
    jsonObjects/jsonObjectObjectsTest.cpp \
    jsonObjects/jsonValueObjectsTest.cpp

HEADERS += \
    parsingTest.h \
    jsonItem/jsonValueItemTest.h \
    jsonItem/jsonObjectItemTest.h \
    jsonItem/jsonArrayItemTest.h \
    jsonObjects/jsonArrayObjectsTest.h \
    jsonObjects/jsonObjectObjectsTest.h \
    jsonObjects/jsonValueObjectsTest.h

