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
#include "ut_displaywidget.h"
#include "stub_dcpdisplaylangconf.h"

#include "dcpdisplaylangconf.h"
#include "displaywidget.h"

#include <MApplication>
#include <MContainer>
#include <QStringListModel>
#include <MList>

void Ut_DisplayWidget::initTestCase()
{
}

void Ut_DisplayWidget::cleanupTestCase()
{
}

void Ut_DisplayWidget::init ()
{
    m_Widget = new DisplayWidget();
}

void Ut_DisplayWidget::cleanup ()
{
    delete m_Widget;
}

void Ut_DisplayWidget::testConstructDestruct()
{
    // tests only that it did not segfault on construction
    QVERIFY(m_Widget->m_List != 0);
}

void Ut_DisplayWidget::testSelectedItem()
{
    // use a new m_Widget after we initialized stub values
/*    delete m_Widget;
    QStringList langList;
    langList << "en" << "fi" << "hu";
    setDcpDisplayLangConfStubAvailableLanguages(langList);
    setDcpDisplayLangConfStubLanguage("fi");
    m_Widget = new DisplayWidget();

    QModelIndexList selection =     
        m_Widget->m_List->selectionModel()->selectedIndexes();
    QCOMPARE(selection.size(), 1);
    QCOMPARE(selection.at(0).data().toString(), QString("fi"));
    
    // test flexibility of the widget, use a current locale id
    // that doesn't match exactly with list ids
    // if en_GB is not listed, it should be mapped to en
    delete m_Widget;
    setDcpDisplayLangConfStubLanguage("en_GB");
    m_Widget = new DisplayWidget();

    selection = m_Widget->m_List->selectionModel()->selectedIndexes();
    QCOMPARE(selection.size(), 1);
    QCOMPARE(selection.at(0).data().toString(), QString("en"));
*/
}

void Ut_DisplayWidget::testOnLanguageSelected()
{
    // fake displayconf to get the result:
/*    
DcpDisplayLangConf* conf = DcpDisplayLangConf::instance();
    conf->setDisplayLanguage(QString("hu_HU"));

    QStringListModel model(QStringList(QString("en_US")));
    m_Widget->onLanguageSelected(model.index(0));
    QCOMPARE(conf->displayLanguage(), QString("en_US"));
*/
}


void Ut_DisplayWidget::testBack()
{
    // checks that the widget wants to return to dcp on back:
    QCOMPARE(m_Widget->back(), true);
}

QTEST_APPLESS_MAIN(Ut_DisplayWidget)
