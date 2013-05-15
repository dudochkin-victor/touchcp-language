include(../ut-head.pri)

TEST_SOURCES = \
		$$PKGROOT/src/dcpdisplaylangconf.cpp \
                $$PKGROOT/tests/stubs/stub_mlocale.cpp \
                $$PKGROOT/tests/stubs/stub_qdir.cpp \
                $$PKGROOT/tests/stubs/stub_regionconfreader.cpp 

HEADERS += \
    $$PKGROOT/src/debug.h \
    $$PKGROOT/src/dcpdisplaylangconf.h \
    $$PKGROOT/src/dcpdisplaylangconf_p.h \
    $$PKGROOT/src/systemcontrol.h \
    $$PKGROOT/tests/stubs/stub_gconfitemprivate.h \
    $$PKGROOT/tests/stubs/stub_mgconfitem.h \
    $$PKGROOT/tests/stubs/stub_mlocale.h \
    $$PKGROOT/tests/stubs/stub_qdir.h \
    $$PKGROOT/tests/stubs/stub_regionconfreader.h \
    *.h

SOURCES += \
    *.cpp \
    $$PKGROOT/src/debug.cpp \
    $$PKGROOT/src/systemcontrol.cpp \
    $$TEST_SOURCES

TARGET = ut_dcpdisplaylangconf

include(../ut-tail.pri)

