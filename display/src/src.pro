TEMPLATE      = lib
CONFIG       += plugin gui meegotouch duicontrolpanel debug

QT += xml

include(../../common.pri)

MOC_DIR	      = ../tmp
OBJECTS_DIR   = ../tmp

HEADERS += $$system(find ./ -name \'*.h\')
SOURCES += $$system(find ./ -name \'*.cpp\')

TARGET        = $$qtLibraryTarget(displaylanguage)
DESTDIR       = ../lib

target.path += $$DCP_APPLET_DIR

message ("Plugin path will be: "$$target.path)

INSTALLS += target

# enable query dialog and shutdown after language change
DEFINES += HAVE_SHUTDOWN

debug {
    DEFINES += DEBUG
    DEFINES += APP_NAME=\\\"\"disp-lang-app\"\\\"
}

# for check:
QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

contains(LANGUAGE_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}
