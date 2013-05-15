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

#include <MAction>
#include <MLibrary>

#include "displaylangapplet.h"
#include "dcpwidget.h"

#include "displaylangbrief.h"
#include "displaywidget.h"

#include "debug.h"

M_LIBRARY
Q_EXPORT_PLUGIN2(displaylangapplet, DisplayLangApplet)

void DisplayLangApplet::init()
{
}

DcpStylableWidget* DisplayLangApplet::constructStylableWidget(int widgetId)
{
    ENTER_FUNCTION();
    Q_UNUSED(widgetId);
    DisplayWidget* widget = new DisplayWidget();
    LEAVE_FUNCTION();
    return widget;
}

QString DisplayLangApplet::title() const
{
    ENTER_FUNCTION();
    //% "Language"
    QString ret = qtTrId("qtn_comm_settings_language");
    LEAVE_FUNCTION();
    return ret;
}

QVector<MAction*> DisplayLangApplet::viewMenuItems()
{
    ENTER_FUNCTION();
    QVector<MAction*> vector;

    // closeAction
    /* MAction *closeAction = new MAction(DcpDisplayLang::QuitSettingsMenuText, this);
    closeAction->setPossibleLocations(MAction::ViewMenu);
    connect(closeAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    vector.push_back(closeAction);*/

    LEAVE_FUNCTION();
    return vector;
}

DcpBrief* DisplayLangApplet::constructBrief(int partId)
{
    ENTER_FUNCTION();
    Q_UNUSED(partId);
    DcpBrief *ret = new DisplayLangBrief();
    LEAVE_FUNCTION();
    return ret;
}

