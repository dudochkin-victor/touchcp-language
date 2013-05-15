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

#include <QStringList>
#include <QDir>
#include <QMap>
#include "stub_qdir.h"

static QStringList qDirStubContent;

void setQDirStubContent(const QStringList &fileNames) {
    qDirStubContent = fileNames;
}

struct QDirStubData {
    QStringList content;
};

struct QDirPrivate : public QSharedData {
};

QMap<const QDir *, QDirStubData> QDirStubMap;

QDir::QDir(const QString &path) {
    QDirStubData data;
    data.content = qDirStubContent;
    QDirStubMap.insert(this, data);
}

QDir::~QDir() {
    QDirStubMap.remove(this);
}

QStringList QDir::entryList(Filters filters, SortFlags sort) const {
    return QDirStubMap[this].content;
}

void QDir::setFilter(Filters) {
}
