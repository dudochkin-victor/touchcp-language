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
#ifndef STUB_GCONFITEMPRIVATE_H
#define STUB_GCONFITEMPRIVATE_H

#include <QString>
#include <QObject>

struct MGConfItemPrivate: public QObject
{
    Q_OBJECT
public:
    QString key;
    void emitChangedSignal() { emit valueChanged(); }
signals:
    void valueChanged();
};

#endif // STUB_GCONFITEMPRIVATE_H
