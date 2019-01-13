win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rd_party/gtest/release/ -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rd_party/gtest/debug/ -lgtest
else:unix:!macx: LIBS += -L$$OUT_PWD/../../3rd_party/gtest/ -lgtest -pthread

INCLUDEPATH += $$PWD/3rd_party/gtest/googletest/include
DEPENDPATH += $$PWD/3rd_party/gtest/googletest/include
SOURCES += $$PWD/3rd_party/gtest/googletest/src/gtest_main.cc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gtest/release/libgtest.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gtest/debug/libgtest.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gtest/release/gtest.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gtest/debug/gtest.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gtest/libgtest.a
