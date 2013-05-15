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
#include "ut_displaylangbrief.h"

#include "displaylangbrief.h"
#include "dcpdisplaylangconf.h"

#include <QSignalSpy>

void Ut_DisplayLangBrief::initTestCase()
{
}

void Ut_DisplayLangBrief::cleanupTestCase()
{
}

void Ut_DisplayLangBrief::init ()
{
}

void Ut_DisplayLangBrief::cleanup ()
{
}

void Ut_DisplayLangBrief::testValueText()
{
    DcpDisplayLangConf* conf = DcpDisplayLangConf::instance();
    conf->setDisplayLanguage("en_US");
    QCOMPARE(DisplayLangBrief().valueText(),
             DcpDisplayLangConf::fullName("en_US"));
}

void Ut_DisplayLangBrief::testValueTextUpdates()
{
    DisplayLangBrief brief;
    DcpDisplayLangConf* conf = DcpDisplayLangConf::instance();
    conf->setDisplayLanguage("hu_HU");

    QSignalSpy spy(&brief, SIGNAL(valuesChanged()));

    // test if brief notices the language change
    conf->setDisplayLanguage("en_US");
    QCOMPARE(spy.count(), 1);
    spy.clear();

    conf->setDisplayLanguage("en_GB");
    QCOMPARE(spy.count(), 1);
    spy.clear();
}

QTEST_APPLESS_MAIN(Ut_DisplayLangBrief)

