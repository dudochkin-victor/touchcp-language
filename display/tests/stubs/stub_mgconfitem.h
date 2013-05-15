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
#ifndef STUB_MGCONFITEM_H
#define STUB_MGCONFITEM_H

#include <MGConfItem>
#include <QHash>
#include <QList>
#include <QtDebug>

#include "stub_gconfitemprivate.h"

// stub class for mgconfitem which simulates its exact work,
// when gconf is working
//
// it simulates the followings:
// - changing a value for a key
// - emitting the itemChanged signal

static QHash<QString, QVariant> gconf_database;
static int gconfItemConstructCount = 0;
static QList<MGConfItemPrivate*> gconfitemprivates;

MGConfItem::MGConfItem  (const QString &key, QObject *parent)
{
    Q_UNUSED(parent);
    priv = new MGConfItemPrivate;
    priv->key = key;
    gconfItemConstructCount++;
    gconfitemprivates.append(this->priv);
    connect (priv, SIGNAL(valueChanged()),
             this, SIGNAL(valueChanged()));
}

MGConfItem::~MGConfItem ()
{
    gconfitemprivates.removeOne(priv);
    delete priv;
    gconfItemConstructCount--;
}

void gconf_changevalue(const QString& key, const QVariant& value)
{
    gconf_database[key] = value;
    foreach(MGConfItemPrivate * priv, gconfitemprivates)
    {
        if (priv->key == key) {
            priv->emitChangedSignal();
        }
    }
}

QString MGConfItem::key () const
{
    return priv->key;
}

QVariant MGConfItem::value () const
{
    return value(QVariant());
}

QVariant MGConfItem::value (const QVariant &def) const
{
    return gconf_database.contains(key()) ? gconf_database.value(key()) : def;
}

void MGConfItem::set (const QVariant &val)
{
    gconf_changevalue(key(), val);
}


#endif // STUB_MGCONFITEM_H

