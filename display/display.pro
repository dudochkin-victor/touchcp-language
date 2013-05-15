TEMPLATE      = subdirs

SUBDIRS += src \
           translations \
           tests

CONFIG += ordered

include(../common.pri)

include (desktop.pri)

style.files = libdisplaylanguage.css
style.path = /usr/share/themes/base/meegotouch/libdisplaylanguage/style

langscript.files = scripts/language.sh
langscript.path = /etc/profile.d
INSTALLS += langscript style

# for check:
QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)
check.CONFIG = recursive

contains(LANGUAGE_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
}

