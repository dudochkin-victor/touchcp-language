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

#include <MLabel>

#include "displaylangitem.h"

DisplayLangItem::DisplayLangItem(QGraphicsItem *parent) :
    MBasicListItem(MBasicListItem::SingleTitle, parent)
{
    setStyleName("CommonPanelInverted");
}

DisplayLangItem::~DisplayLangItem()
{
}

QGraphicsLayout *DisplayLangItem::createLayout()
{
    QGraphicsLayout *layout = MBasicListItem::createLayout();
    titleLabelWidget()->setStyleName("CommonSingleTitleInverted");
    return layout;
}

void DisplayLangItem::clearLayout()
{
    MBasicListItem::clearLayout();
}

