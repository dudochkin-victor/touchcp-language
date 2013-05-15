/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel-languageapplet.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/
#include "ut_dcpdisplaylangconf.h"

#include "dcpdisplaylangconf_params.h"
#include "dcpdisplaylangconf.h"
#include "dcpdisplaylangconf_p.h"
#include "stub_mgconfitem.h"
#include "stub_mlocale.h"
#include "stub_qdir.h"
#include "stub_regionconfreader.h"

static const QString l10nGConfPath = "/meegotouch/i18n";
static const QString enabledVkbLayoutsGConfPath = 
    "/meegotouch/inputmethods/virtualkeyboard/layouts";
static const QString defaultVkbLayoutGConfPath =
    "/meegotouch/inputmethods/virtualkeyboard/layouts/default";
static const QString userSelectedRegionGConfPath =
    "/meegotouch/i18n/userselectedregion";
static const QString regionGConfPath =
    "/meegotouch/i18n/region";

void Ut_DcpDisplayLangConf::initTestCase()
{
}

void Ut_DcpDisplayLangConf::cleanupTestCase()
{
}

void Ut_DcpDisplayLangConf::init ()
{
}

void Ut_DcpDisplayLangConf::cleanup ()
{
}

/**
 * Test the proper script dependent ordering of the available languages
 */
void Ut_DcpDisplayLangConf::testAvailableDisplayLanguagesSort()
{
    QFETCH(QString, currentLocaleId);
    QFETCH(QStringList, fileNames);
    QFETCH(QStringList, localeIds);

    setQDirStubContent(fileNames);
    setDefaultStubMLocaleId(currentLocaleId);
    QStringList result =
        DcpDisplayLangConf::instance()->availableDisplayLanguages();
    QCOMPARE(result, localeIds);
}

void Ut_DcpDisplayLangConf::testAvailableDisplayLanguagesSort_data()
{
    QTest::addColumn<QString>("currentLocaleId");
    QTest::addColumn<QStringList>("fileNames");
    QTest::addColumn<QStringList>("localeIds");

    QStringList qDirContent;
    qDirContent << "de" << "fi" << "ru" << "uk" << "cs";

    QStringList latinExpected;
    latinExpected << "cs" << "de" << "fi" << "ru" << "uk";
    QTest::newRow("latin script") << "de" << qDirContent << latinExpected;

    QStringList cyrExpected;
    cyrExpected << "ru" << "uk" << "cs" << "de" << "fi";
    QTest::newRow("cyrillic script") << "ru" << qDirContent << cyrExpected;
}

/**
 * Test if "en" and its variants are handled properly
 */
void Ut_DcpDisplayLangConf::testAvailableDisplayLanguagesIdConvert()
{
    QFETCH(QString, fileName);
    QFETCH(QString, localeId);

    QStringList qDirContent(fileName);
    setQDirStubContent(qDirContent);
    QStringList expected(localeId);
    QStringList result =
        DcpDisplayLangConf::instance()->availableDisplayLanguages();
    QCOMPARE(result, expected);
}

void Ut_DcpDisplayLangConf::testAvailableDisplayLanguagesIdConvert_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("localeId");

    QTest::newRow("en") << "en" << "en_GB";
    QTest::newRow("en_GB") << "en_GB" << "en_GB";
    QTest::newRow("en_US") << "en_US" << "en_US";
}
 
void Ut_DcpDisplayLangConf::testDisplayLanguageChange()
{
    DcpDisplayLangConf::instance()->setDisplayLanguage("en_US");
    QCOMPARE(DcpDisplayLangConf::instance()->displayLanguage(), QString("en_US"));
}

void Ut_DcpDisplayLangConf::testDisplayLanguageChangedSignal()
{
    // set something which we can change
    DcpDisplayLangConf::instance()->setDisplayLanguage("en_US");

    QSignalSpy spy(DcpDisplayLangConf::instance(),
                   SIGNAL(displayLanguageChanged()));

    // test if the signal is emitted when we change through DcpDisplayLangConf
    DcpDisplayLangConf::instance()->setDisplayLanguage("fi");
    QCOMPARE(spy.count(), 1);
    spy.clear();

    // test if the signal is emitted when we change from outside
    MGConfItem("/meegotouch/i18n/language").set("fi");
    QCOMPARE(spy.count(), 1);
    spy.clear();
}

void Ut_DcpDisplayLangConf::testFullName()
{
    DcpDisplayLangConf* conf = DcpDisplayLangConf::instance();
    // empty locale id
    QVERIFY(conf->fullName(QString()).isEmpty());
    
    // valid locale id, with faked MLocale::languageEndonym()  
    // test upper casing too
    QCOMPARE(conf->fullName("de"), QString("De endonym"));
}

void Ut_DcpDisplayLangConf::testIsLanguagesSet()
{
    MGConfItem(l10nGConfPath).set(QVariant());
    QVERIFY (!DcpDisplayLangConf::instance()->isLanguagesSet());
    DcpDisplayLangConf::instance()->setDisplayLanguage("en_US");
    QVERIFY (DcpDisplayLangConf::instance()->isLanguagesSet());
}

void Ut_DcpDisplayLangConf::testConstructDestruct()
{
    QVERIFY (DcpDisplayLangConf::instance() != 0);
    DcpDisplayLangConf::freeSingleton();
    QVERIFY (DcpDisplayLangConf::sm_Instance == 0);
//    QCOMPARE (gconfItemConstructCount, 0); FIXME? or a singleton in the bg? XXX
    QVERIFY (DcpDisplayLangConf::instance() != 0);
}

void Ut_DcpDisplayLangConf::testSettingBadLanguage()
{
    QSKIP("Not implemented, maybe not even necessery", SkipSingle);

#if 0    
    // set a good language:
    DcpDisplayLangConf::instance()->setDisplayLanguage("en_US");
    // set a wrong language, which is not in the availables
    DcpDisplayLangConf::instance()->setDisplayLanguage("he_HE");
    // the language did not changed:
    QCOMPARE(DcpDisplayLangConf::instance()->displayLanguage(), QString("en_US"));
#endif    
}

void Ut_DcpDisplayLangConf::testUpdateVkbLayout()
{
    QFETCH(QStringList, installedLayouts);
    QFETCH(QStringList, enabledLayouts);
    QFETCH(QString, languageId);
    QFETCH(QStringList, expectedEnabledLayouts);
    QFETCH(QString, expectedDefaultLayout);

    setQDirStubContent(installedLayouts);
    MGConfItem enabledVkbLayoutsGConf(enabledVkbLayoutsGConfPath);
    enabledVkbLayoutsGConf.set(enabledLayouts);

    DcpDisplayLangConf *conf = DcpDisplayLangConf::instance();
    conf->d_ptr->updateVkbLayout(languageId);
    QCOMPARE(enabledVkbLayoutsGConf.value().toStringList(),
             expectedEnabledLayouts);
    QCOMPARE(MGConfItem(defaultVkbLayoutGConfPath).value().toString(),
             expectedDefaultLayout);
}

void Ut_DcpDisplayLangConf::testUpdateVkbLayout_data()
{
    QTest::addColumn<QStringList>("installedLayouts");
    QTest::addColumn<QStringList>("enabledLayouts");
    QTest::addColumn<QString>("languageId");
    QTest::addColumn<QStringList>("expectedEnabledLayouts");
    QTest::addColumn<QString>("expectedDefaultLayout");

    QStringList layoutFiles;
    layoutFiles << "en_gb.xml" << "fr_ca.xml" << "es_mx.xml" << "hu.xml";
    QStringList enabled;

    enabled << "fr_ca.xml";
    QTest::newRow("exact match with country") << layoutFiles << enabled 
        << "fr_CA" << enabled << "fr_ca.xml";

    enabled.clear();
    enabled << "hu.xml";
    QTest::newRow("exact match without country") << layoutFiles << enabled
        << "hu" << enabled << "hu.xml";

    enabled.clear();
    enabled << "hu.xml";
    QTest::newRow("language match") << layoutFiles << enabled << "hu_HU" <<
        enabled << "hu.xml";

    enabled.clear();
    enabled << "en_gb.xml" << "fr_ca.xml" << "es_mx.xml";
    QStringList newEnabled(enabled);
    newEnabled << "hu.xml";
    QTest::newRow("new enabled") << layoutFiles << enabled << "hu" <<
        newEnabled << "hu.xml";

    enabled.clear();
    enabled = layoutFiles;
    QTest::newRow("no matching layout") << layoutFiles << enabled << "xx" <<
        enabled << "en_gb.xml";
}

void Ut_DcpDisplayLangConf::testUpdateRegion() 
{
    QFETCH(QStringList, availableRegions);
    QFETCH(QString, language);
    QFETCH(QString, expectedRegion);

    MGConfItem(userSelectedRegionGConfPath).set(false);
    setAvailableRegions(availableRegions);
    MGConfItem(regionGConfPath).set("xx_XX");
    DcpDisplayLangConf *conf = DcpDisplayLangConf::instance();
    conf->d_ptr->updateRegionFormat(language);
    QCOMPARE(MGConfItem(regionGConfPath).value().toString(),
             expectedRegion);
}

void Ut_DcpDisplayLangConf::testUpdateRegion_data() 
{
    QTest::addColumn<QStringList>("availableRegions");
    QTest::addColumn<QString>("language");
    QTest::addColumn<QString>("expectedRegion");

    QStringList regions;
    regions << "en_GB" << "en_US" << "cs_CZ" << "hu_HU" << "de_DE" << "de_AT";

    QTest::newRow("en") << regions << "en" << "en_GB";
    QTest::newRow("en_GB") << regions << "en_GB" << "en_GB";
    QTest::newRow("en_US") << regions << "en_US" << "en_US";
    QTest::newRow("exact match1") << regions << "hu_HU" << "hu_HU";
    QTest::newRow("exact match2") << regions << "de_AT" << "de_AT";
    QTest::newRow("partial match1") << regions << "hu" << "hu_HU";
    QTest::newRow("partial match2") << regions << "cs" << "cs_CZ";
    QTest::newRow("partial match3") << regions << "de" << "de_DE";
}

int main (int argc, char** argv) {
    // run the test:
    Ut_DcpDisplayLangConf test;
    return QTest::qExec(&test, argc, argv);
}


