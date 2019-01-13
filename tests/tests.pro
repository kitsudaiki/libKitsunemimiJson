include(../defaults.pri)

QT -= qt core gui

CONFIG -= app_bundle
CONFIG += c++14 console


LIBS += -L../../libKitsuneCommon -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/debug -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/release -lKitsuneCommon
INCLUDEPATH += ../../../libKitsuneCommon/include/libKitsuneCommon


INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneJson

SOURCES += \
        main.cpp \
    jsonArrayTest.cpp \
    jsonObjectTest.cpp \
    jsonValueTest.cpp \
    parsingTest.cpp

HEADERS += \
    jsonArrayTest.h \
    jsonValueTest.h \
    jsonObjectTest.h \
    parsingTest.h

