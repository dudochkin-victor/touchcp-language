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

#include <dcpdisplaylangconf.h>
#include <QDebug>
#include "languagemodel.h"
     
LangData::LangData(const QString& lang)
{
    code = lang;
    name = DcpDisplayLangConf::instance()->fullName(lang);
};

LanguageModel& LanguageModel::instance()
{
    qDebug() << Q_FUNC_INFO;                                                                                      
    static LanguageModel model;
    model.setObjectName("LanguageModel");
    return model;
}


LanguageModel::LanguageModel(QObject *parent) :
    MAbstractItemModel(parent)
{
    populateModel();
}

LanguageModel::~LanguageModel()
{
}

// return invalid index if language not found in model
QModelIndex LanguageModel::getIndex(const QString &language) const
{
    if (!m_LanguageIndexMap.contains(language)) {
        qWarning() << "language not in model:" << language;
        return QModelIndex();
    }

    QVector<int> indexVec = m_LanguageIndexMap[language];
    QModelIndex parent = index(indexVec[0], 0);
    QModelIndex idx = index(indexVec[1], 0, parent);
    return idx;
}

void LanguageModel::populateModel()
{
    
    DcpDisplayLangConf* conf = DcpDisplayLangConf::instance();
    QStringList availableLangs = conf->availableDisplayLanguages();
    foreach (QString lang, availableLangs)
    {
        LangData data = LangData(lang);
	m_Languages.append(data);
        QChar label = data.name[0];
        int groupIndex = m_GroupLabels.indexOf(label);
        if (groupIndex == -1) {
              m_GroupLabels.append(label);
              groupIndex = m_GroupLabels.count() - 1;
        }
        m_GroupMap[groupIndex].append(data);
        QVector<int> indexVec(2);
        indexVec[0] = groupIndex;
        indexVec[1] = m_GroupMap[groupIndex].count() - 1;
        m_LanguageIndexMap[data.name] = indexVec;
    } 
}

void LanguageModel::updateData(const QModelIndex &first, const QModelIndex &last)
{
    emit dataChanged(first, last);
}

int LanguageModel::groupCount() const
{
    return m_GroupLabels.count();
}
int LanguageModel::rowCountInGroup(int group) const
{
    if (group == -1) {
        return m_Languages.count();
    }

    return m_GroupMap[group].count();
}

QString LanguageModel::groupTitle(int group) const
{
    if (group > -1 && group < m_GroupLabels.count())
        return m_GroupLabels[group];
    
    return QString();
}

QVariant LanguageModel::itemData(int row, int group, int role) const
{

    LangData language("");
    if (group >= 0 && row >= 0) {                                                         
        language = m_GroupMap[group].at(row);                                                    
    } else {                                                                              
        language = m_Languages.at(row);                                                             
    }              
    	QStringList list;
   switch (role)
   {
     case DisplayRole:
        list << language.code << language.name;
        return QVariant(list);                   
     default:
	return QVariant(language.name);
   }
}

