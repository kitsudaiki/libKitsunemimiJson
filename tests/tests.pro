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
    libKitsuneJson/jsonItem_parseString_test.cpp \
    libKitsuneJson/jsonItem_test.cpp

HEADERS += \
    libKitsuneJson/jsonItem_parseString_test.hpp \
    libKitsuneJson/jsonItem_test.hpp

