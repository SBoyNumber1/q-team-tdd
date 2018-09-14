TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    include \
    ../gtest/googletest/include \
    ../gtest/googletest \
    ../gtest

SOURCES += \
    src/gmock-all.cc \
    src/gmock_main.cc \
    ../gtest/googletest/src/gtest-all.cc

HEADERS += \
    include/gmock/internal/* \
    include/gmock/*
