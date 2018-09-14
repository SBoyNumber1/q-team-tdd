include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    socketwrapper.cpp \
    socketwrappertest.cpp

LIBS += \
    Ws2_32.lib \
    Mswsock.lib \
    AdvApi32.lib

HEADERS += \
    socketwrapper.h \
    mocks.h \
    isocketwrapper.h \
    igui.h
