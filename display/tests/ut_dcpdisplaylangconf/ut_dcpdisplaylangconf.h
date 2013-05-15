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
#ifndef UT_DCPDISPLAYLANGCONF_H
#define UT_DCPDISPLAYLANGCONF_H

#include <QtTest/QtTest>
#include <QObject>

class Ut_DcpDisplayLangConf: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testIsLanguagesSet();
    void testAvailableDisplayLanguagesSort();
    void testAvailableDisplayLanguagesSort_data();
    void testAvailableDisplayLanguagesIdConvert();
    void testAvailableDisplayLanguagesIdConvert_data();
    void testDisplayLanguageChange();
    void testDisplayLanguageChangedSignal();
    void testFullName();
    void testConstructDestruct();
    void testSettingBadLanguage();
    void testUpdateVkbLayout();
    void testUpdateVkbLayout_data();
    void testUpdateRegion();
    void testUpdateRegion_data();
};


#endif // UT_DCPDISPLAYLANGCONF_H

