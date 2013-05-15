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
#include "ut_displaylangitem.h"

#include "displaylangitem.h"

// disables output messages to be able to see the test result
void myMsgHandler(QtMsgType, const char *) { }

void Ut_DisplayLangItem::initTestCase()
{
    qInstallMsgHandler(myMsgHandler);
}

void Ut_DisplayLangItem::cleanupTestCase()
{
}

void Ut_DisplayLangItem::init ()
{
    m_Subject = new DisplayLangItem();
}

void Ut_DisplayLangItem::cleanup ()
{
    delete m_Subject;
}

void Ut_DisplayLangItem::testConstructDestruct()
{
}

void Ut_DisplayLangItem::testStyleNames()
{
    // TODO... It might need some excessive stubbing :P
}


QTEST_APPLESS_MAIN(Ut_DisplayLangItem)

