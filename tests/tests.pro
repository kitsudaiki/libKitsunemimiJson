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
    libKitsuneJson/jsonItems_JsonArray_test.cpp \
    libKitsuneJson/jsonItems_JsonObject_test.cpp \
    libKitsuneJson/jsonItems_JsonValue_test.cpp \
    libKitsuneJson/jsonItems_parseString_test.cpp

HEADERS += \
    libKitsuneJson/jsonItems_JsonArray_test.hpp \
    libKitsuneJson/jsonItems_JsonObject_test.hpp \
    libKitsuneJson/jsonItems_JsonValue_test.hpp \
    libKitsuneJson/jsonItems_parseString_test.hpp

