include ($$[QT_INSTALL_DATA]/mkspecs/dcpconfig.pri)
CONFIG += warn_on

release=$$(RELEASE)
contains(release, "yes") {
    CONFIG += release
}

BASEPATH = $$DCP_PREFIX/share/duicontrolpanel-displaylanguageapplet
DEFINES += BASEPATH=\\\"\"$$BASEPATH\"\\\"

LANGDATA_DIR = /var/lib/duicontrolpanel-displaylanguageapplet
LANGDATA_PATH = $${LANGDATA_DIR}/lang
DEFINES += LANGDATA_PATH=\\\"$${LANGDATA_PATH}\\\"
