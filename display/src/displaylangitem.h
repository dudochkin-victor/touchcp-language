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

#ifndef DISPLAY_LANG_ITEM_H__
#define DISPLAY_LANG_ITEM_H__

#include <MBasicListItem>

class DisplayLangItem : public MBasicListItem
{
    Q_OBJECT

    public:
        DisplayLangItem(QGraphicsItem *parent=0);
        virtual ~DisplayLangItem();

    protected:
        virtual QGraphicsLayout *createLayout();
        virtual void clearLayout();

#ifdef UNIT_TEST        
    friend class Ut_DisplayLangItem;
#endif
};

#endif // DISPLAY_LANG_ITEM_H__
