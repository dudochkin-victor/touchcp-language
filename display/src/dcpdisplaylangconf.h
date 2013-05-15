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

#ifndef DCP_DISPLAY_LANG_CONF_H
#define DCP_DISPLAY_LANG_CONF_H

#include <QStringList>

class DcpDisplayLangConfPrivate;

/**
 \class DcpDisplayLangConf
 \brief This class is used to set and query active display language,
 and list which languages are available.
*/
class DcpDisplayLangConf: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DcpDisplayLangConf)
    Q_DECLARE_PRIVATE(DcpDisplayLangConf);
public:
    static DcpDisplayLangConf *instance();
    static void freeSingleton();
    ~DcpDisplayLangConf();

    /**
     * \brief Returns currently selected display language
     */
    QString displayLanguage();

    /// returns if the languages are set by user or not
    bool isLanguagesSet();

    /**
     *\brief Sets current display language
     */
    void setDisplayLanguage(QString displayLanguage);

    /**
     *\brief Returns a list of all available display languages
     */
    QStringList availableDisplayLanguages();

    /**
     *\brief Returns a string in form "language (country)" in their own language.
     *       Country is ommitted if same as language or not found.
     */
    static QString fullName(const QString &lang);

signals:
    void displayLanguageChanged();

protected:
    DcpDisplayLangConf();

private:
    static DcpDisplayLangConf *sm_Instance;

    //! point to private data
    DcpDisplayLangConfPrivate * d_ptr;

#ifdef UNIT_TEST
    friend class Ut_DcpDisplayLangConf;
#endif
};

#endif // DCP_DISPLAY_LANG_CONF_H

