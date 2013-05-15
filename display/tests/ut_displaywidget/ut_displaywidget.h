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
#ifndef UT_DISPLAYWIDGET_H
#define UT_DISPLAYWIDGET_H

#include <QtTest/QtTest>
#include <QObject>

class Ut_DisplayWidget: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testConstructDestruct();
    void testSelectedItem();
    void testOnLanguageSelected();
    void testBack();

private:
    class DisplayWidget* m_Widget;
};


#endif // UT_DISPLAYWIDGET

