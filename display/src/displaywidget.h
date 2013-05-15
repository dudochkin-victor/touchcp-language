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

#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QModelIndex>
#include <DcpStylableWidget>
class MMessageBox;
class MSceneWindow;

class DisplayWidget : public DcpStylableWidget
{
    Q_OBJECT

public:
    DisplayWidget();
    virtual bool back();
    virtual ~DisplayWidget();

protected slots:
    virtual void onLanguageSelected(const QModelIndex&);
    void onChangeLanguageDialogAccepted();
    void onChangeLanguageDialogRejected();
    void startSpinner();
    void changeLanguageAndClose();
    void changeOrientation(M::Orientation orientation);
    void scrollToSelected();
    void liveFilteringTextChangedSlot();
    void hideEmptyTextEdit(); 
    void filteringVKBSlot();
    void showTextEdit(bool show);
    void displayEnteredSlot();
    
protected:
    void initWidget();
    QString title() const;

    virtual void polishEvent();
	
private:
    QModelIndex currentLanguageProxyIndex();
    QModelIndex translateModelIndex(const QModelIndex &languageModelIndex);
    void selectCurrentLanguage();
    class DisplayLangCellCreator* m_CellCreator;
    class MList* m_List;
    MMessageBox *m_ChangeLanguageDialog;
    QString m_SelectedLanguage;
    MSceneWindow *m_SpinnerWindow;

#ifdef UNIT_TEST
    friend class Ut_DisplayWidget;
#endif
};

#endif //DISPLAYWIDGET_H

