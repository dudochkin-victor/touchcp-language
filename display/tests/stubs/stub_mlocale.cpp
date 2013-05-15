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

#include <QMap>
#include <QString>
#include <QStringList>
#include <MLocale>
#include "stub_mlocale.h"

QString defaultStubMLocaleId = "en";

void setDefaultStubMLocaleId(const QString &id) {
    defaultStubMLocaleId = id;
}

struct MLocaleStubData {
    QString localeId;
};

#define STUBDATA() MLocaleStubMap[this]

QMap<const MLocale*,MLocaleStubData> MLocaleStubMap;

MLocale::MLocale(QObject *parent) 
    : QObject(parent),
      d_ptr(0)
{
    MLocaleStubData data;
    data.localeId = defaultStubMLocaleId;
    MLocaleStubMap.insert(this, data);
}

MLocale::MLocale(const QString &localeName, QObject *parent) 
    : QObject(parent),
      d_ptr(0)
{
    MLocaleStubData data;
    data.localeId = localeName;
    MLocaleStubMap.insert(this, data);
}

MLocale::~MLocale() {
    MLocaleStubMap.remove(this);
}

// static
QString MLocale::languageEndonym(const QString &localeId) {
    // some special test locale ids with test endonym strings
    if (localeId.startsWith("cs")) {
        QString str;
        // Creating cestina unicode string
        str += QChar(0x010d); // latin small letter c with caron
        str += 'e';
        str += QChar(0x0161); // latin small letter s with caron        
        str += "tina";
        return str;
    }
    if (localeId.startsWith("ru")) {
        QString str;
        str += QChar(0x0440); // cyrillic small letter er
        str += QChar(0x0443); // cyrillic small letter u
        return str;
    }
    if (localeId.startsWith("uk")) {
        QString str;
        str += QChar(0x0443); // cyrillic small letter u
        str += QChar(0x043a); // cyrillic small letter ka
        return str;
    }
    if (localeId.startsWith("ar")) {
        QString str;
        str += QChar(0x0627); // arabic letter alef
        str += QChar(0x0631); // arabic letter reh
        return str;
    }

    return localeId + " endonym";
}

QString MLocale::languageEndonym() const {
    QString localeId(STUBDATA().localeId);
    return MLocale::languageEndonym(localeId);
}

QString MLocale::name() const {
    return STUBDATA().localeId;
}

QString MLocale::script() const {
    return QString();
}

// static
QString MLocale::localeScript(const QString &localeName) {
    if (localeName.startsWith("ru") || localeName.startsWith("uk")) {
        return "Cyrl";
    } else if (localeName.startsWith("ar")) {
        return "Arab";
    } else {
        return "Latn";
    }
}

QStringList MLocale::localeScripts() const {
    QString localeName(STUBDATA().localeId);
    QStringList list;
    list << MLocale::localeScript(localeName);
    return list;
}

MLocale &MLocale::operator=(const MLocale &other) {
    STUBDATA().localeId = MLocaleStubMap[&other].localeId;
}
