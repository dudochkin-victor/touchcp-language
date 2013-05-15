
INCLUDEPATH += ./ \
              $$PKGROOT/tests/stubs \
              $$PKGROOT/src \

DEPENDPATH += $$INCLUDEPATH

INSTALLS += target

check.depends = $$TARGET
check.commands = @LD_LIBRARY_PATH=$$PKGROOT/lib:$$(LD_LIBRARY_PATH) ./$$TARGET
QMAKE_EXTRA_TARGETS += check

QMAKE_CLEAN += *.log.xml *.log
QMAKE_CLEAN += *.gcda *.gcno *.gcov

