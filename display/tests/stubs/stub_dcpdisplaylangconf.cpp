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
#include "dcpdisplaylangconf.h"
#include <QStringList>

DcpDisplayLangConf* DcpDisplayLangConf::sm_Instance = NULL;
static QString language = "hu_HU";
static QStringList availableLangs(language);

void setDcpDisplayLangConfStubLanguage(const QString &langid) {
    language = langid;
}

void setDcpDisplayLangConfStubAvailableLanguages(const QStringList &langList) {
    availableLangs = langList;
}

DcpDisplayLangConf::DcpDisplayLangConf() : d_ptr(0) { }
DcpDisplayLangConf::~DcpDisplayLangConf() { }

DcpDisplayLangConf* DcpDisplayLangConf::instance()
{
    if (!sm_Instance) {
        sm_Instance = new DcpDisplayLangConf();
    }
    return sm_Instance;
}

void DcpDisplayLangConf::freeSingleton(){}

QString DcpDisplayLangConf::displayLanguage() { return language; }

void DcpDisplayLangConf::setDisplayLanguage(const QString lang)
{
    language = lang;
    emit displayLanguageChanged();
}

bool DcpDisplayLangConf::isLanguagesSet() { return true; }

QStringList DcpDisplayLangConf::availableDisplayLanguages()
{
    return availableLangs;
}

QString DcpDisplayLangConf::fullName(const QString& lang)
{
    return lang+"Full";
}


