include(../ut-head.pri)

INCLUDEPATH += $$system(find $$PKGROOT -type d)

TARGET = ut_languagemodel

TEST_SOURCES = \
    $$PKGROOT/src/languagemodel.cpp \

# unit test and unit
SOURCES += \
    ut_languagemodel.cpp \
    $$PKGROOT/tests/stubs/stub_dcpdisplaylangconf.cpp \
    $$TEST_SOURCES \ 

# base classes
SOURCES += \


# unit test and unit
HEADERS += \
    ut_languagemodel.h \
    $$PKGROOT/tests/stubs/stub_dcpdisplaylangconf.h \
    $$PKGROOT/src/dcpdisplaylangconf.h \
    $$PKGROOT/src/languagemodel.h \

# base classes
HEADERS += \


# service classes
HEADERS += \

include(../ut-tail.pri)

