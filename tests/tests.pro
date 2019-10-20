include(../defaults.pri)

QT -= qt core gui

CONFIG -= app_bundle
CONFIG += c++14 console


LIBS += -L../../libKitsuneCommon/src -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/src/debug -lKitsuneCommon
LIBS += -L../../libKitsuneCommon/src/release -lKitsuneCommon
INCLUDEPATH += ../../libKitsuneCommon/include


INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneJson

SOURCES += \
    main.cpp \
    libKitsuneJson/json_item_parseString_test.cpp \
    libKitsuneJson/json_item_test.cpp

HEADERS += \
    libKitsuneJson/json_item_parseString_test.h \
    libKitsuneJson/json_item_test.h

