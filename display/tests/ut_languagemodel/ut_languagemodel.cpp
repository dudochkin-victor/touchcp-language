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

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QSignalSpy>


#include "ut_languagemodel.h"

void Ut_LanguageModel::init()
{
}

void Ut_LanguageModel::cleanup()
{
}

void Ut_LanguageModel::initTestCase()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_LanguageModel::cleanupTestCase()
{
}

void Ut_LanguageModel::testInstance()
{
    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
    QVERIFY(&model == &(LanguageModel::instance()));
}

void Ut_LanguageModel::testGroupCount()
{
    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
    QCOMPARE(model.groupCount(), model.m_GroupLabels.count());
}

void Ut_LanguageModel::testRowCountInGroup()
{
    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
    QCOMPARE(model.rowCountInGroup(-1), model.m_Languages.count());
    for (int i=0;i < model.m_GroupMap.keys().count(); i++)
        QCOMPARE(model.rowCountInGroup(i), model.m_GroupMap[i].count());
}

void Ut_LanguageModel::testGroupTitle()
{

    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
    for (int i=0;i < model.m_GroupLabels.count(); i++)
        QCOMPARE(model.groupTitle(i), QString(model.m_GroupLabels[i]));
    int badIdx = model.m_GroupLabels.count();
    QCOMPARE(model.groupTitle(badIdx), QString());
    badIdx = -1;
    QCOMPARE(model.groupTitle(badIdx), QString());
}

void Ut_LanguageModel::testUpdateData()
{
    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
    QSignalSpy spy(&model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)));
    model.updateData(QModelIndex(), QModelIndex());
    QCOMPARE(spy.count(), 1);
    model.updateData(QModelIndex(), QModelIndex());
    QCOMPARE(spy.count(), 2);
}

void Ut_LanguageModel::testItemData()
{
    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
}

void Ut_LanguageModel::testGetIndex()
{
    QSKIP("incomplete", SkipSingle);   // remove this when you've finished
}

void Ut_LanguageModel::testPopulateModel()
{
}


void Ut_LanguageModel::testGroupLabel()
{
    LanguageModel &model = LanguageModel::instance();
    model.setGrouped(true);
}


QTEST_APPLESS_MAIN(Ut_LanguageModel)
