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

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QFile>
#include <QtDebug>

#include "regionconfreader.h"

static const QString SupportedRegionsConf = "/etc/meego-supported-regions.conf";

QStringList RegionConfReader::availableRegions()
{
    QFile regionsConf(SupportedRegionsConf);
    if (!regionsConf.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "unable to open " << SupportedRegionsConf << ": " <<
            regionsConf.errorString();
        return QStringList();
    }

    QStringList result;
    QTextStream inStream(&regionsConf);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        QStringList fields = line.split(" ", QString::SkipEmptyParts);
        result << fields[1];
    }

    return result;
}

