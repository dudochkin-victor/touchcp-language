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
#ifndef DISPLAYLANGCELLCREATOR_H
#define DISPLAYLANGCELLCREATOR_H

#include <MAbstractCellCreator>
#include "displaylangitem.h"

class DisplayLangCellCreator: public MAbstractCellCreator<DisplayLangItem>
{
public:
      virtual void updateCell(const QModelIndex& index, MWidget * cell) const;
      QString formatText(QString text) const;
      void highlightByText(QString text) {
            highlightText = text;
        }
      QString highlightText;
      
};


#endif // DISPLAYLANGCELLCREATOR_H

