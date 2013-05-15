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
/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <MAbstractItemModel>


class LangData {
public:
     LangData(const QString& lang);
     QString code;
     QString name;
};

class LanguageModel : public MAbstractItemModel {
    Q_OBJECT

    public:
        static LanguageModel& instance();
        ~LanguageModel();
        int groupCount() const;
        int rowCountInGroup(int group) const;
        QString groupTitle(int group) const;
        void updateData(const QModelIndex &first, const QModelIndex &last);
        QVariant itemData(int row, int group, int role) const;
        enum Columns {
            Code = 0,
            Name,
            NumberOfColumns
        };

        enum ItemDataRole {
            SortRole = Qt::UserRole+1,
            DisplayRole,
            FilterRole,
	    RoleCount,
        };


        QModelIndex getIndex(const QString &language) const;
        void populateModel();
    private:
        LanguageModel(QObject *parent=0);

        QList<LangData> m_Languages;   
        QList<QChar> m_GroupLabels;                                                
        QMap<int, QList<LangData> > m_GroupMap;   
        // lamguage -> (group, row) index vector
        QMap<QString, QVector<int> > m_LanguageIndexMap;
        friend class Ut_LanguageModel;
};


#endif

