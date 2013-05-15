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
/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <MLocale>
#include <MGConfItem>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QTemporaryFile>
#include <QRegExp>
#include <QApplication>

#include <cstdio>
#include <cerrno>
#include <cstring>

#include "dcpdisplaylangconf.h"
#include "dcpdisplaylangconf_p.h"
#include "systemcontrol.h"
#include "regionconfreader.h"

#undef DEBUG
#include "debug.h"

namespace GConfKey
{
    const QString RegionRoot("/meegotouch/i18n");
    const QString SettingsLanguage("/meegotouch/i18n/language");
    const QString UserSelectedRegion("/meegotouch/i18n/userselectedregion");
    const QString EnabledVkbLayouts( 
                   "/meegotouch/inputmethods/virtualkeyboard/layouts");
    const QString DefaultVkbLayout(
                   "/meegotouch/inputmethods/virtualkeyboard/layouts/default");

}

const char *RegionKeys[] = {
    "region", "lc_monetary", "lc_collate", "lc_time", "lc_numeric", 
    // terminate with 0!
    0
};


static const QString SupportedLanguagesDir = "/etc/meego-supported-languages";
static const QString LanguageFile = LANGDATA_PATH;
static const QString VkbLayoutDir = 
    "/usr/share/meegotouch/virtual-keyboard/layouts";

DcpDisplayLangConf *DcpDisplayLangConf::sm_Instance = 0;


DcpDisplayLangConf*
DcpDisplayLangConf::instance()
{
    ENTER_STATIC_FUNCTION();
    if (!sm_Instance)
        sm_Instance = new DcpDisplayLangConf();

    LEAVE_STATIC_FUNCTION();
    return sm_Instance;
}

void
DcpDisplayLangConf::freeSingleton()
{
    ENTER_STATIC_FUNCTION();
    if (sm_Instance) {
        delete sm_Instance;
        sm_Instance = 0;
    }
    LEAVE_STATIC_FUNCTION();
}

DcpDisplayLangConf::DcpDisplayLangConf() :
  d_ptr(new DcpDisplayLangConfPrivate)
{
    ENTER_FUNCTION();
    Q_D(DcpDisplayLangConf);
    // connect config change signals:
    connect (d->m_DisplayLanguageItem, SIGNAL(valueChanged()),
             this, SIGNAL(displayLanguageChanged()));
    LEAVE_FUNCTION();
}

DcpDisplayLangConf::~DcpDisplayLangConf()
{
    ENTER_FUNCTION();
    delete d_ptr;
    d_ptr = 0;
    LEAVE_FUNCTION();
}

bool
DcpDisplayLangConf::isLanguagesSet()
{
    ENTER_FUNCTION();
    Q_D(DcpDisplayLangConf);
    bool ret = d->isLanguagesSet();
    LEAVE_FUNCTION();
    return ret;
}

// Display language specific

QString
DcpDisplayLangConf::displayLanguage()
{
    ENTER_FUNCTION();
    Q_D(DcpDisplayLangConf);
    QString ret = d->displayLanguage();
    LEAVE_FUNCTION();
    return ret;
}

void
DcpDisplayLangConf::setDisplayLanguage(QString displayLanguage)
{
    ENTER_FUNCTION();
    Q_D(DcpDisplayLangConf);
    d->setDisplayLanguage(displayLanguage);
    LEAVE_FUNCTION();
}

QStringList
DcpDisplayLangConf::availableDisplayLanguages()
{
    ENTER_FUNCTION();
    Q_D(DcpDisplayLangConf);
    QStringList ret = d->availableDisplayLanguages();
    LEAVE_FUNCTION();
    return ret;
}

QString
DcpDisplayLangConf::fullName (
        const QString &lang)
{
    ENTER_STATIC_FUNCTION();
    QString ret = DcpDisplayLangConfPrivate::fullName(lang);
    LEAVE_STATIC_FUNCTION();
    return ret;
}


// Private class implementation

DcpDisplayLangConfPrivate::DcpDisplayLangConfPrivate() :
    m_DisplayLanguageItem(new MGConfItem(GConfKey::SettingsLanguage))
{
    ENTER_FUNCTION();
    LEAVE_FUNCTION();
}

bool
DcpDisplayLangConfPrivate::isLanguagesSet()
{
    ENTER_FUNCTION();
    bool ret = !m_DisplayLanguageItem->value().toString().isEmpty();
    LEAVE_FUNCTION();
    return ret;
}

void
DcpDisplayLangConfPrivate::setRegionFormat(const QString &localeID)
{
    ENTER_FUNCTION();
    int i = 0;
    while (RegionKeys[i]) {
        MGConfItem gconf(GConfKey::RegionRoot + "/" + RegionKeys[i]);
        gconf.set(localeID);
        ++i;
    }
    LEAVE_FUNCTION();
}

DcpDisplayLangConfPrivate::~DcpDisplayLangConfPrivate()
{
    ENTER_FUNCTION();
    delete m_DisplayLanguageItem;
    LEAVE_FUNCTION();
}

// Display language specific

QString DcpDisplayLangConfPrivate::displayLanguage()
{
    ENTER_FUNCTION();
    QString result = m_DisplayLanguageItem->value().toString();
    if (result.isEmpty()) {
        result = MLocale().name(); // returning the default
    }

    LEAVE_FUNCTION();
    return result;
}

/*!
 * \param displayLanguage A language code with or without the country code,
 * should be contained by availableLanguages()
 *
 * This function takes a language code with or without the country code part
 * (like 'de' or 'de_DE') and stores as the new display language setting for the
 * MLocale object. 
 *
 */
void 
DcpDisplayLangConfPrivate::setDisplayLanguage (QString displayLanguage)
{
    /*
     * Here we use the qLocale to interpret the language name and choose a
     * default country if necessary.
     */
    QString fixedLanguage = displayLanguage;

    m_DisplayLanguageItem->set(fixedLanguage);

    /* check if setting was changed by our trial */
    QString oldLanguage = this->displayLanguage();
    if (oldLanguage != fixedLanguage) {
        /* FIXME this is a hack to notify suw that user changed some setting,
         * ! use MGConfItem api instead */
        QSettings suwstate("startup/state");
        suwstate.setValue("settings-changed-by-user", true);
    }

    // write the language to a file so it can be read in boot time
#ifndef UNIT_TEST
    QFile tmpFile(LanguageFile + ".new");
    if (tmpFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&tmpFile);
        out << displayLanguage << "\n";
        tmpFile.close();
        // use libc function for atomic update
        if (std::rename(tmpFile.fileName().toUtf8().data(),
                        LanguageFile.toUtf8().data()) != 0) {
            qWarning("updating %s failed: %s", qPrintable(LanguageFile),
                     std::strerror(errno));
        }
    } else {
        qWarning("updating %s failed (not able to create a temporary file)",
                 qPrintable(LanguageFile));
    }
#endif    

    updateRegionFormat(displayLanguage);

    if (qApp->applicationName() == MStartupAppName) {
        updateVkbLayout(displayLanguage);
    }

    LEAVE_FUNCTION();
}

void 
DcpDisplayLangConfPrivate::updateRegionFormat(const QString &langLocaleId)
{
    MGConfItem userSelectedRegion(GConfKey::UserSelectedRegion);
    if (!userSelectedRegion.value().toBool()) {
        // user didn't touch the region settings, set it automatically
        // to one that matches the language
        // TODO: use a more reliable mapping
        QString region;
        if (langLocaleId == "en") {
            region = "en_GB";
        } else if (langLocaleId == "es_419") {
           // do nothing, there's no unique country that matches this
        } else {
            RegionConfReader conf;
            foreach (QString r, conf.availableRegions()) {
                if (langLocaleId == r) {
                    region = r;
                    // exact match, finished
                    break;
                }
                // in partial match with xx language xx_XX region has
                // higher priority than xx_YY
                if (r.startsWith(langLocaleId + "_") &&
                    (region.isEmpty() ||
                     langLocaleId + "_" + langLocaleId.toUpper() == r)) {
                    region = r;
                    // partial match, let's continue the iteration
                }
            }
        }

        if (!region.isEmpty()) {
            setRegionFormat(region);
        } else {
            qWarning() << "couldnt find a suitable region for " << langLocaleId;
        }
    }
}

QStringList DcpDisplayLangConfPrivate::availableVkbLayouts()
{
    QStringList result;
    QDir vkbLayoutsDir(VkbLayoutDir);
    vkbLayoutsDir.setFilter(QDir::Files | QDir::NoDotAndDotDot | 
                            QDir::NoSymLinks);
    foreach (QString fileName, vkbLayoutsDir.entryList()) {
        QRegExp mask("[a-z][a-z](_[a-z][a-z])?\\.xml");
        if (!mask.exactMatch(fileName)) {
            continue;
        }
        result << fileName;
    }
    return result;
}

void
DcpDisplayLangConfPrivate::updateVkbLayout(const QString &langLocaleId)
{
    QStringList availableLayouts = availableVkbLayouts();
    QString fallbackLayout = "en_gb.xml";
    QString mexicanLayout = "es_mx.xml";
    QString fullMatchLayout = langLocaleId.toLower() + ".xml";
    QString langMatchLayout = langLocaleId.left(2) + ".xml";
    QString layout;
    if (langLocaleId == "es_419" && availableLayouts.contains("es_mx.xml")) {
        layout = "es_mx.xml";
    } else if (availableLayouts.contains(fullMatchLayout)) {
        layout = fullMatchLayout;
    } else if (availableLayouts.contains(langMatchLayout)) {
        layout = langMatchLayout;
    } else {
        qWarning() << "not found a suitable vkb layout for " << langLocaleId;
        layout = fallbackLayout;
    }

    // add the layout to the enabled layouts if it's not there yet
    MGConfItem layoutsGConf(GConfKey::EnabledVkbLayouts);
    if (layoutsGConf.value().type() == QVariant::StringList) {
        QStringList enabledLayouts = layoutsGConf.value().toStringList();
        if (!enabledLayouts.contains(layout)) {
            enabledLayouts.append(layout);
            layoutsGConf.set(enabledLayouts);
        }
    } else {
        qWarning() << GConfKey::EnabledVkbLayouts << " is not a string list";
    }

    // set default layout
    MGConfItem defaultLayoutGConf(GConfKey::DefaultVkbLayout);
    defaultLayoutGConf.set(layout);
}

/**
 * return an unambigous script class for the localeId locale
 * if localeId is null (QString()) then use current locale
 */
DcpDisplayLangConfPrivate::ScriptClass 
DcpDisplayLangConfPrivate::scriptClass(const QString &localeId)
{
    QString s;
    if (localeId.isNull()) {
        MLocale loc;

        s = loc.script();
        if (s.isEmpty())
            s = loc.localeScripts().first();
    } else {
        s = MLocale::localeScript(localeId);
    }

    if (s == "Latn") return ScriptClassLatin;
    if (s == "Arab") return ScriptClassArabic;
    if (s == "Cyrl") return ScriptClassCyrillic;


    return ScriptClassOther;
}

/**
 * returns locale Id's in the same order that their list items 
 * shall appear in the ui
 */
QStringList DcpDisplayLangConfPrivate::availableDisplayLanguages()
{
    ENTER_FUNCTION();
   
    QMap<int,QStringList> scriptIdListMap;

    // get available language locales from SupportedLanguagesDir
    QDir supportedLangDir(SupportedLanguagesDir);
    supportedLangDir.setFilter(QDir::Files | QDir::NoDotAndDotDot | 
                               QDir::NoSymLinks);

    foreach (QString fileName, supportedLangDir.entryList()) {
        QString localeId = fileName;
        // special case: en means British English and country needs to be
        // made explicit because some other components (MLocale, mstartup) 
        // expect this
        if (localeId == "en") {
            localeId = "en_GB";
        }

        DcpDisplayLangConfPrivate::ScriptClass script = scriptClass(localeId);
        scriptIdListMap[script].append(localeId);
        qDebug() << "have locale" << localeId << "script" << script;
    }

    DcpDisplayLangConfPrivate::ScriptClass currentScript = scriptClass();
    QStringList sortedIdList;
    QList<int> scriptOrder;
    // languages with current script come first
    scriptOrder.append(currentScript);
    // the order of the other scripts
    for(int i = ScriptClassLatin; i < ScriptClassLast; ++i) {
        if (i != currentScript) {
            scriptOrder.append(i);
        }
    }

    foreach (int i, scriptOrder) {
        // sort each language with a given script based on
        // their fullName in case insensitive way
        // decompose all precomposed characters to get 
        // proper ordering of accented characters
        // eg. 'c with caron should' should preceed 'd'
        // we are using multimap because fullnames can be identical
        // (however this indicates a bug in MLocale)
        QMultiMap<QString,QString> sortMap;
        foreach (QString localeId, scriptIdListMap[i]) {
            QString sortKey = fullName(localeId).toLower();
            qDebug() << "sortkey" << sortKey.toUtf8().toHex();
            sortKey = sortKey.normalized(QString::NormalizationForm_D);
            sortMap.insert(sortKey, localeId);
        }
        foreach (QString localeId, sortMap.values()) {
            sortedIdList.append(localeId);
        }
    }

    LEAVE_FUNCTION();
    return sortedIdList;
}


QString
DcpDisplayLangConfPrivate::fullName (
        const QString &lang)
{
    //PRINT_DEBUG ("*** lang = '%s'", STR(lang));

    ENTER_STATIC_FUNCTION();
    if (lang.isEmpty()){
        LEAVE_STATIC_FUNCTION();
        return lang;
    }

    // special case: en means British English and country needs to be
    // made explicit to get the correct language endonym
    QString normLang = lang;
    if (normLang == "en") {
        normLang = "en_GB";
    }
    QString result = MLocale::languageEndonym(normLang);
    if (!result.isEmpty()) {
        result[0] = result[0].toUpper();
    }

    #if 0
    PRINT_DEBUG ("*** language  = '%s'", STR(locale.language()));
    PRINT_DEBUG ("*** country   = '%s'", STR(locale.country()));
    PRINT_DEBUG ("*** script    = '%s'", STR(locale.script()));
    PRINT_DEBUG ("*** variant   = '%s'", STR(locale.variant()));
    PRINT_DEBUG ("*** name      = '%s'", STR(locale.name()));
    PRINT_DEBUG ("*** cendonym  = '%s'", STR(locale.countryEndonym()));
    PRINT_DEBUG ("*** lendonym  = '%s'", STR(locale.languageEndonym()));
    #endif

    LEAVE_STATIC_FUNCTION();

    //PRINT_DEBUG ("Returning '%s'", STR(result));
    return result;
}

QStringList DcpDisplayLangConfPrivate::defaultLanguages()
{
    ENTER_FUNCTION();
    QStringList languageList;
/*
    languageList << "da_DA" << "de_DE" << "en_GB" << "en_US" 
            << "fr_CA" << "fr_FR" << "it_IT" << "es_ES" << "nl_NL" << "no_NO"
            << "pt_PT" << "pt_BR" << "RU" << "fi_FI";
 */
    languageList << "en_GB";
    LEAVE_FUNCTION();
    return languageList;
}

