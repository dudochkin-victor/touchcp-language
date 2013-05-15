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

#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QString>
#include <QApplication>
#include <QFileInfo>
#include "systemcontrol.h"

static const int FullScreenTimeout = 5000;
const char *MStartupAppName = "Meego Startup Wizard";
const char *NoRebootFile = "/tmp/LANG_NO_REBOOT";

SystemControl::SystemControl() {}

SystemControl::~SystemControl() {}

void SystemControl::showFullScreenMessage(const QString &msg1, 
                                          const QString &msg2) {
    QDBusInterface shutdownUiIf("com.nokia.systemui",
                                "/",
                                "com.nokia.systemui.shutdownui");
    shutdownUiIf.call("showScreen", msg1, msg2, FullScreenTimeout);
}

void SystemControl::reboot() {
    QDBusInterface dsmeIf("com.nokia.dsme",
                          "/com/nokia/dsme/request",
                          "com.nokia.dsme.request",
                          QDBusConnection::systemBus());
    dsmeIf.call("req_reboot");
}

bool SystemControl::needToRebootAfterLanguageChange() {
#ifndef HAVE_SHUTDOWN
    return false;
#else
    if (qApp->applicationName() == MStartupAppName) {
        return false;
    }
    QFileInfo fileInfo(NoRebootFile);
    return !fileInfo.exists();
#endif    
}
