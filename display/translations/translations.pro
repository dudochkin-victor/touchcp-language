LANGUAGES =
CATALOGNAME = language
SOURCEDIR = $$PWD/../src
TRANSLATIONDIR = $$PWD
TRANSLATION_INSTALLDIR = /usr/share/l10n/meegotouch
include(../../translations.pri)

# for check:
QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)

contains(LANGUAGE_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.commands = $$system(true)
}
