TEMPLATE = subdirs

CONFIG += debug
CONFIG += build_all silent

SUBDIRS += display \
#          tests \
#          examples

# for check:
QMAKE_EXTRA_TARGETS += check
check.commands = $$system(true)
check.CONFIG = recursive

contains(LANGUAGE_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.depends = display/src/Makefile
  coverage.commands =    cd display && make coverage && cd .. \
                      && genhtml --no-branch-coverage --legend -t \"languagesettings unit test coverage\" -o coverage/ display/tests/ut*/selected.cov

  QMAKE_DISTCLEAN += -r coverage/*
}
