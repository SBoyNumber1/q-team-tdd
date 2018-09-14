TEMPLATE = lib
CONFIG += c++11
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += \
    googletest/include \
    googletest

SOURCES += \
    googletest/src/gtest-all.cc \
    googletest/src/gtest_main.cc

HEADERS += \
    googletest/include/gtest/internal/custom/gtest-port.h \
    googletest/include/gtest/internal/custom/gtest-printers.h \
    googletest/include/gtest/internal/custom/gtest.h \
    googletest/include/gtest/internal/gtest-death-test-internal.h \
    googletest/include/gtest/internal/gtest-filepath.h \
    googletest/include/gtest/internal/gtest-internal.h \
    googletest/include/gtest/internal/gtest-linked_ptr.h \
    googletest/include/gtest/internal/gtest-param-util-generated.h \
    googletest/include/gtest/internal/gtest-param-util.h \
    googletest/include/gtest/internal/gtest-port-arch.h \
    googletest/include/gtest/internal/gtest-port.h \
    googletest/include/gtest/internal/gtest-string.h \
    googletest/include/gtest/internal/gtest-tuple.h \
    googletest/include/gtest/internal/gtest-type-util.h \
    googletest/include/gtest/gtest-death-test.h \
    googletest/include/gtest/gtest-message.h \
    googletest/include/gtest/gtest-param-test.h \
    googletest/include/gtest/gtest-printers.h \
    googletest/include/gtest/gtest-spi.h \
    googletest/include/gtest/gtest-test-part.h \
    googletest/include/gtest/gtest-typed-test.h \
    googletest/include/gtest/gtest.h \
    googletest/include/gtest/gtest_pred_impl.h \
    googletest/include/gtest/gtest_prod.h
