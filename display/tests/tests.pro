TEMPLATE    = subdirs

!include(../../common.pri){
	message( "common.pri can not be found" )
}


contains(LANGUAGE_BUILD_FEATURES,coverage) {
  SUBDIRS = $$system(ls -1d ut_*/)
} else {
  SUBDIRS = $$system(ls -1d ut_*/)
}


check.CONFIG += recursive
QMAKE_EXTRA_TARGETS += check

shell_scripts.commands += ./gen-tests-xml.sh > tests.xml
shell_scripts.files += tests.xml
shell_scripts.path += $$DCP_PREFIX/share/duicontrolpanel-displaylanguageapplet-tests
shell_scripts.CONFIG += no_check_exist

INSTALLS += shell_scripts

# ldd can not find the applet so in its regular place even if LD_LIBRARY_PATH
# contains its absolute path. Relative path would work with ldd but only if
# the current library the test is executed in is not a sibling path of the
# directory /usr/lib/duicontrolpanel/applets.
# Installing one another instance into /usr/lib makes ldd happy however.
# Symlink not seems to be enough.
#applet-copy.files += ../lib/libdisplaylanguage.so
#applet-copy.path += $$DCP_PREFIX/lib
#INSTALLS += applet-copy

QMAKE_CLEAN += tests.xml

contains(LANGUAGE_BUILD_FEATURES,coverage) {
  QMAKE_EXTRA_TARGETS += coverage
  coverage.target = coverage
  coverage.CONFIG = recursive
}


