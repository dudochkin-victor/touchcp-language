include(../ut-head.pri)

CONFIG += duicontrolpanel
#LIBS += $$PKGROOT/lib/libdisplaylanguage.so

TEST_SOURCES = \
    $$PKGROOT/src/displaywidget.cpp \
    $$PKGROOT/tests/stubs/qgraphicslayoutitem-fake.cpp \
    $$PKGROOT/tests/stubs/qgraphicslinearlayout-fake.cpp \
    $$PKGROOT/tests/stubs/mwidgetcontroller-fake.cpp \
    $$PKGROOT/tests/stubs/mtheme-fake.cpp \
    $$PKGROOT/tests/stubs/mtextedit-fake.cpp \
    $$PKGROOT/tests/stubs/mapplication-fake.cpp \
    $$PKGROOT/tests/stubs/mapplicationwindow-fake.cpp \
    $$PKGROOT/tests/stubs/mabstractlayoutpolicy-fake.cpp \
    $$PKGROOT/tests/stubs/mlayout-fake.cpp \
    $$PKGROOT/tests/stubs/mlinearlayoutpolicy-fake.cpp \
    $$PKGROOT/tests/stubs/qgraphicsobject-fake.cpp \
    $$PKGROOT/tests/stubs/mimagewidget-fake.cpp \
    $$PKGROOT/tests/stubs/mlistfilter-fake.cpp \
    $$PKGROOT/tests/stubs/mlist-fake.cpp \
    $$PKGROOT/tests/stubs/mbasiclistitem-fake.cpp \

HEADERS += *.h \
    $$PKGROOT/src/debug.h \
    $$PKGROOT/src/dcpdisplaylangconf.h \
    $$PKGROOT/src/displaywidget.h \
    $$PKGROOT/src/displaylangcellcreator.h \
    $$PKGROOT/src/displaylangitem.h \
    $$PKGROOT/src/languagemodel.h \
    $$PKGROOT/tests/stubs/stub_dcpdisplaylangconf.h

SOURCES += *.cpp \
    $$PKGROOT/src/debug.cpp \
    $$PKGROOT/tests/stubs/stub_dcpdisplaylangconf.cpp \
    $$PKGROOT/src/displaylangitem.cpp \
    $$PKGROOT/src/languagemodel.cpp \
    $$PKGROOT/tests/stubs/stub_systemcontrol.cpp \
    $$TEST_SOURCES

TARGET = ut_displaywidget

include(../ut-tail.pri)

