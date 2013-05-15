include(../ut-head.pri)

TEST_SOURCES = \
		$$PKGROOT/src/systemcontrol.cpp

HEADERS += *.h \
	$$PKGROOT/src/systemcontrol.h \

SOURCES += *.cpp \
	$$TEST_SOURCES

TARGET = ut_systemcontrol

include(../ut-tail.pri)

# data files to install:
# QMAKE_EXTRA_TARGET += ut_systemcontrol_data
# ut_systemcontrol_data.files += .../*
# ut_systemcontrol_data.path = $$UT_INSTALL_DIR/...
# INSTALLS += ut_systemcontrol_data

