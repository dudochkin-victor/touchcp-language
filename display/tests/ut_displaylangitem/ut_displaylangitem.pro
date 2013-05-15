include(../ut-head.pri)

TEST_SOURCES = \
		$$PKGROOT/src/displaylangitem.cpp

HEADERS += *.h \
	$$PKGROOT/src/displaylangitem.h \

SOURCES += *.cpp \
	$$TEST_SOURCES

TARGET = ut_displaylangitem

include(../ut-tail.pri)

# data files to install:
# QMAKE_EXTRA_TARGET += ut_displaylangitem_data
# ut_displaylangitem_data.files += .../*
# ut_displaylangitem_data.path = $$UT_INSTALL_DIR/...
# INSTALLS += ut_displaylangitem_data

