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
#include <dcpappletmetadata.h>
#include <QFileInfo>

/* This is used with appletloader for checking if the applet is
 * loadable. */

QString
DcpAppletMetadata::fullBinary () const
{
    QString filename = "libdisplaylanguage.so";

    // for the local version (without install)
    QString path = "../../lib/" + filename;
    if (QFileInfo(path).exists()) return path;

    // installed version of the test
    return "/usr/lib/duicontrolpanel/applets/" + filename;
}

