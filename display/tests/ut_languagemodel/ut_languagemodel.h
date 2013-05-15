/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel-datetimeapplet.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#ifndef UT_LANGUAGEMODEL_H
#define UT_LANGUAGEMODEL_H

#include <QtTest/QtTest>
#include <QObject>

// the real unit/LanguageModel class declaration
#include <languagemodel.h>
Q_DECLARE_METATYPE(LanguageModel*);

class Ut_LanguageModel : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testInstance();
    void testGroupCount();
    void testRowCountInGroup();
    void testGroupTitle();
    void testUpdateData();
    void testItemData();
    void testGetIndex();
    void testPopulateModel();
    void testGroupLabel();
    

private:
};

#endif
