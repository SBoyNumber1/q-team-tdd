win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rd_party/gmock/release/ -lgmock
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rd_party/gmock/debug/ -lgmock
else:unix: LIBS += -L$$OUT_PWD/../../3rd_party/gmock/ -lgmock -pthread

INCLUDEPATH += $$PWD/3rd_party/gmock/include
INCLUDEPATH += $$PWD/3rd_party/gtest/googletest/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gmock/release/libgmock.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gmock/debug/libgmock.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gmock/release/gmock.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gmock/debug/gmock.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rd_party/gmock/libgmock.a
