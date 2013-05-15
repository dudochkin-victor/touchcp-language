include(../ut-head.pri)

TEST_SOURCES = \
#		$$PKGROOT/src/template.cpp

HEADERS += *.h \
#	$$PKGROOT/src/template.h \

SOURCES += *.cpp \
	$$TEST_SOURCES

TARGET = ut_template

include(../ut-tail.pri)

# data files to install:
# QMAKE_EXTRA_TARGET += ut_template_data
# ut_template_data.files += .../*
# ut_template_data.path = $$UT_INSTALL_DIR/...
# INSTALLS += ut_template_data

