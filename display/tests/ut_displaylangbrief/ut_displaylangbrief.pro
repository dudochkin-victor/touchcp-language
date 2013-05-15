include(../ut-head.pri)

CONFIG+=duicontrolpanel

TEST_SOURCES = \
    $$PKGROOT/src/displaylangbrief.cpp

HEADERS += *.h \
    $$PKGROOT/src/dcpdisplaylangconf.h \
    $$PKGROOT/src/displaylangbrief.h \
    $$PKGROOT/src/debug.h

SOURCES += *.cpp \
    $$PKGROOT/tests/stubs/stub_dcpdisplaylangconf.cpp \
    $$PKGROOT/src/debug.cpp \
    $$TEST_SOURCES

TARGET = ut_displaylangbrief

include(../ut-tail.pri)

