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

#include "displaywidget.h"

#include "dcpdisplaylangconf.h"
#include "systemcontrol.h"

#include <QtDebug>
#include <QTimer>
#include <MList>
#include <mwidgetcreator.h>
#include <MAbstractItemModel>
#include <QSortFilterProxyModel>
#include <MListFilter>
#include <MSortFilterProxyModel>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QModelIndex>
#include <MOrientationChangeEvent>
#include <MSceneManager>
#include <MApplication>
#include <MMessageBox>
#include <MLabel>
#include <MLayout>
#include <MLinearLayoutPolicy>
#include <MTextEdit>
#include <MStylableWidget>
#include <MModalSceneWindow>
#include <MProgressIndicator>
#include <MWidgetView>
#include "languagemodel.h"
#include "debug.h"
#include "displaylangcellcreator.h"

#define SCROLL_DELAY 1 // immediate scrolling doesn't work...
#define LANG_CHANGE_DELAY 1000 

void DisplayLangCellCreator::updateCell(
        const QModelIndex& index, MWidget * cell) const
{
   if (!cell){ /* happens to be null when shortening filter string */
        return;
    }
    if(!index.isValid()){ /* happens to be invalid when filtered to be empty */
        return;
    }

    DisplayLangItem * contentItem = qobject_cast<DisplayLangItem *>(cell);
    if (!contentItem)
       return;
    QStringList data = index.data(LanguageModel::DisplayRole).toStringList();
    contentItem->setTitle(formatText(data[LanguageModel::Name]));
}

QString DisplayLangCellCreator::formatText(QString text) const
{
    if (highlightText.isEmpty())
        return text;

    QString result = text;
    int matchingIndex = result.indexOf(highlightText, 0, Qt::CaseInsensitive);
        if(matchingIndex != -1) {
            qDebug() << "Highlighting";
            result.insert(matchingIndex+highlightText.length(), "</b>");
            result.insert(matchingIndex, "<b>");
        }
    return result;
}

M_REGISTER_WIDGET_NO_CREATE (DisplayWidget)

DisplayWidget::DisplayWidget()
              :DcpStylableWidget(),
               m_SpinnerWindow(0)
{
    ENTER_FUNCTION();
    initWidget();
    LEAVE_FUNCTION();
}

DisplayWidget::~DisplayWidget()
{
    ENTER_FUNCTION();
    delete m_ChangeLanguageDialog;
    LEAVE_FUNCTION();
}

void DisplayWidget::initWidget()
{
    ENTER_FUNCTION();

    installEventFilter(this);
    
    MLayout *mainLayout = new MLayout(this);
    setLayout(mainLayout);

    MLinearLayoutPolicy *mainLayoutPolicy =
        new MLinearLayoutPolicy(mainLayout, Qt::Vertical);
    mainLayout->setPolicy(mainLayoutPolicy);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayoutPolicy->setStyleName("DisplayWidgetMainLayoutPolicy");
    
/*
    QGraphicsLinearLayout * layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
*/
    
    MStylableWidget *titleWidget = new MStylableWidget(this);
    titleWidget->setStyleName("CommonXLargeHeaderPanelInverted");
    QGraphicsLinearLayout * titleLayout = new QGraphicsLinearLayout(titleWidget);
    titleLayout->setContentsMargins(0, 0, 0, 0);
    MLabel *titleLabel = new MLabel(qtTrId("qtn_comm_settings_language"), titleWidget);
    titleLabel->setStyleName("CommonXLargeHeaderInverted");
    titleLayout->addItem (titleLabel);
    titleWidget->setLayout(titleLayout);
    titleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    MStylableWidget *spacer1 = new MStylableWidget(this);
    spacer1->setStyleName("CommonSmallSpacer");

    m_List = new MList();
    m_List->setObjectName("DisplayWidgetMList");
    m_List->setStyleName("CommonListInverted");
    m_CellCreator = new DisplayLangCellCreator();
    m_List->setCellCreator(m_CellCreator);
    m_List->setSelectionMode(MList::SingleSelection);
    
    m_List->setShowGroups(true);
    MAbstractItemModel *model = &(LanguageModel::instance());
    model->setGrouped(true);
    MSortFilterProxyModel *proxyModel = new MSortFilterProxyModel();
    proxyModel->setSortRole(LanguageModel::SortRole);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterRole(LanguageModel::FilterRole);
    proxyModel->setSourceModel(model);
    proxyModel->sort(Qt::AscendingOrder);

    m_List->setItemModel(proxyModel);
    m_List->setShowGroups(true);
    m_List->setIndexVisible(true);
    MListFilter *filter = m_List->filtering();

    filter->setEnabled(true);
//    filter->setFilterMode(MListFilter::FilterAsBeginningOfLine);

    filter->setFilterMode(MListFilter::FilterByApplication);
    filter->setFilterRole(LanguageModel::FilterRole);
    filter->editor()->setVisible(false);

    connect(filter, SIGNAL(listPannedUpFromTop()),
            this, SLOT(filteringVKBSlot())); 
    connect(filter->editor(), SIGNAL(textChanged()),
            this, SLOT(liveFilteringTextChangedSlot())); 

    retranslateUi();

    connect(this, SIGNAL(displayEntered()),
            this, SLOT(displayEnteredSlot()));

    connect (m_List, SIGNAL(itemClicked(QModelIndex)),
             this, SLOT(onLanguageSelected(QModelIndex)));
#ifdef TWOCOLUMNMODE
    connect(MApplication::activeWindow(),
            SIGNAL(orientationChanged(M::Orientation)),
            this, SLOT(changeOrientation(M::Orientation)));
#endif

    mainLayoutPolicy->addItem(titleWidget);
    mainLayoutPolicy->addItem(spacer1);
    if (model->groupCount() == 0) {
        MLabel *label = new MLabel("No language installed", this);
        label->setStyleName("CommonSingleTitleInverted");
        mainLayoutPolicy->addItem(label);
    } else {
       mainLayoutPolicy->addItem(m_List);
    }

    //% "Change device language? The device will reboot, temporarily disabling all functions, including emergency calls."
    m_ChangeLanguageDialog = new MMessageBox(qtTrId("qtn_lang_change_title"),
					     qtTrId("qtn_lang_change_query"),
                                             M::YesButton | M::NoButton);
    connect(m_ChangeLanguageDialog, SIGNAL(accepted()),
            this, SLOT(onChangeLanguageDialogAccepted()));
    connect(m_ChangeLanguageDialog, SIGNAL(rejected()),
            this, SLOT(onChangeLanguageDialogRejected()));


    LEAVE_FUNCTION();
}

void DisplayWidget::displayEnteredSlot()
{
    // scrollTo works only in this delayed way
    qDebug() << Q_FUNC_INFO;
    QTimer::singleShot(1, this, SLOT(scrollToSelected()));
    m_List->setFocus();
}
QString DisplayWidget::title() const
{
    //% "Language"
    const char *widgetTitle = QT_TRID_NOOP("qtn_comm_settings_language");
    return QString(qtTrId(widgetTitle));
}

void DisplayWidget::onLanguageSelected(const QModelIndex &index)
{ 
    qDebug() << Q_FUNC_INFO;
    if (!index.isValid()) {
	qWarning("Selected index is invalid"); 
        return;
    }

    QStringList list = index.data(LanguageModel::DisplayRole).toStringList();
    qDebug() << "selected:" << list;
    m_SelectedLanguage = list[LanguageModel::Code];
    QString currentLangCode = 
        DcpDisplayLangConf::instance()->displayLanguage();
    if (m_SelectedLanguage == currentLangCode) {
        return;
    }
    if (SystemControl::needToRebootAfterLanguageChange()) {
        m_ChangeLanguageDialog->appear();
    } else {
        onChangeLanguageDialogAccepted();
    }
}

void DisplayWidget::onChangeLanguageDialogAccepted()
{
    qDebug() << Q_FUNC_INFO;

    if (SystemControl::needToRebootAfterLanguageChange()) {
        SystemControl syscont;
        syscont.showFullScreenMessage(
                                      //% "Changing language"
                                      qtTrId("qtn_lang_change_down"),
                                      //% "Please wait!"
                                      qtTrId("qtn_lang_wait"));
        changeLanguageAndClose();

    } else {
        startSpinner();

        // do a delayed language change, let enough time
        // to the spinner to appear
        QTimer::singleShot(LANG_CHANGE_DELAY, this, 
                           SLOT(changeLanguageAndClose()));
    }
}

void DisplayWidget::onChangeLanguageDialogRejected()
{
    selectCurrentLanguage();
}

void DisplayWidget::startSpinner()
{
    m_SpinnerWindow = new MModalSceneWindow();
    m_SpinnerWindow->setStyleName("SpinnerWindow");
    MProgressIndicator *spinner = new MProgressIndicator(m_SpinnerWindow, 
                                             MProgressIndicator::spinnerType);
    spinner->setUnknownDuration(true);
    spinner->setStyleName("CommonLargeSpinnerInverted");
    QGraphicsGridLayout *layout = new QGraphicsGridLayout();
    m_SpinnerWindow->setLayout(layout);
    layout->addItem(spinner, 1, 1);
    // didnt find any other way to center the spinner to the screen than
    // inserting it into a stretching grid
    layout->setRowStretchFactor(0, 1);
    layout->setRowStretchFactor(2, 1);
    layout->setColumnStretchFactor(0, 1);
    layout->setColumnStretchFactor(2, 1);
    m_SpinnerWindow->appear(MApplication::activeWindow(), 
                             MSceneWindow::DestroyWhenDone);
}

void DisplayWidget::changeLanguageAndClose() 
{
    DcpDisplayLangConf* conf = DcpDisplayLangConf::instance();
    conf->setDisplayLanguage(m_SelectedLanguage);

    // if we do a shutdown, don't close language page because
    // it would happen before full screen message would appear
    // due to the slowness of the interaction with systemui
    if (SystemControl::needToRebootAfterLanguageChange()) {
        SystemControl syscont;
        syscont.reboot();
    } else {
        m_SpinnerWindow->disappear();
        m_SpinnerWindow = 0;
        emit closePage();
    }
}

void DisplayWidget::selectCurrentLanguage()
{
    m_List->filtering()->editor()->clear();
    // temporary disconnect the signal
    disconnect(m_List, SIGNAL(itemClicked(QModelIndex)),            
               this, SLOT(onLanguageSelected(QModelIndex)));
    m_List->selectItem(currentLanguageProxyIndex());
    connect(m_List, SIGNAL(itemClicked(QModelIndex)),
            this, SLOT(onLanguageSelected(QModelIndex)));
  //  scrollToSelected();
    m_List->setFocus();
}

bool DisplayWidget::back()
{
    qDebug() << Q_FUNC_INFO;
    m_List->filtering()->editor()->clear();
    if(m_List->filtering()->editor()->isOnDisplay())
        showTextEdit(false);
    return DcpStylableWidget::back();
}
void DisplayWidget::polishEvent()
{
#ifdef TWOCOLUMNMODE
    if (sceneManager()) {
    qDebug() << Q_FUNC_INFO;
        changeOrientation(sceneManager()->orientation());
    }
#endif
}

void DisplayWidget::scrollToSelected()
{
    qDebug() << Q_FUNC_INFO;

    QModelIndex proxyIdx = currentLanguageProxyIndex();
    if (proxyIdx.isValid()) {
        QVariant data = proxyIdx.data(Qt::DisplayRole);
        QString rowData = data.toString();

        qDebug() << rowData;
        m_List->scrollTo(proxyIdx, MList::PositionAtTopHint);
  
        // temporary disconnect the signal
        disconnect(m_List, SIGNAL(itemClicked(QModelIndex)),            
                   this, SLOT(onLanguageSelected(QModelIndex)));
        m_List->selectItem(proxyIdx);
	connect(m_List, SIGNAL(itemClicked(QModelIndex)),
                this, SLOT(onLanguageSelected(QModelIndex)));
        m_List->setFocus();

    } else {
        qWarning("selected index is not valid!");
    }
        m_List->setIndexDisplayMode(MList::Floating);

}

void DisplayWidget::changeOrientation(M::Orientation orientation)
{
    qDebug() << Q_FUNC_INFO;
 
#ifdef TWOCOLUMNMODE
    int columns = 2;
    if (orientation == M::Portrait) {
        columns = 1;
    }
    m_List->setColumns(columns);
#else
     Q_UNUSED(orientation);
#endif
}

QModelIndex DisplayWidget::currentLanguageProxyIndex()
{
    qDebug() << Q_FUNC_INFO;

    DcpDisplayLangConf *conf = DcpDisplayLangConf::instance();
    QString lang = conf->displayLanguage();
    QString fullName = conf->fullName(lang);
    QModelIndex sourceIdx = LanguageModel::instance().getIndex(fullName);    
    QModelIndex proxyIdx = translateModelIndex(sourceIdx);

    return proxyIdx;
}

void DisplayWidget::liveFilteringTextChangedSlot()
{
    // With HWKB live filtering text edit is hidden when empty and shown when user enters text
    qDebug() << Q_FUNC_INFO;
    if(m_List->filtering()->editor()->text() == "" && m_List->filtering()->editor()->isOnDisplay())
    QTimer::singleShot(1500, this, SLOT(hideEmptyTextEdit()));
    else if(m_List->filtering()->editor()->text() != "" && !m_List->filtering()->editor()->isOnDisplay())
        showTextEdit(true);
 
    QString filter = QRegExp::escape(m_List->filtering()->editor()->text());
    QRegExp::PatternSyntax syntax = QRegExp::RegExp;
    Qt::CaseSensitivity caseSensitivity = Qt::CaseInsensitive;
    QRegExp regExp("^" + filter, caseSensitivity, syntax);
    m_List->filtering()->proxy()->setFilterRegExp(regExp);    
   
  m_CellCreator->highlightByText(filter);
  LanguageModel *model = qobject_cast<LanguageModel*>(m_List->itemModel());
  if (model) 
 {
    qDebug() << "updateData";
    model->updateData(m_List->firstVisibleItem(), m_List->lastVisibleItem()); 	  
 }
}

void DisplayWidget::hideEmptyTextEdit() {
    qDebug() << Q_FUNC_INFO;
    if(m_List->filtering()->enabled() && m_List->filtering()->editor()->text() == "") {
        showTextEdit(false);
        qDebug() << "Hiding Textedit";
        selectCurrentLanguage();
    }
}

void DisplayWidget::filteringVKBSlot()
{
    qDebug() << Q_FUNC_INFO;
    if(!m_List->filtering()->editor()->isOnDisplay()) {
        showTextEdit(true);
        m_List->filtering()->editor()->setFocus();
    }
}

void DisplayWidget::showTextEdit(bool show) {
    qDebug() << Q_FUNC_INFO;
    MTextEdit* textEdit = m_List->filtering()->editor();
    MLayout *mlayout = dynamic_cast<MLayout*>(layout());
    MLinearLayoutPolicy *mainLayoutPolicy;
    if (!mlayout) {
        return;
    }

    mainLayoutPolicy = dynamic_cast<MLinearLayoutPolicy*>(mlayout->policy());

    if (mainLayoutPolicy) {
        if (show && !textEdit->isOnDisplay()) {
            qDebug() << "Textedit is visible";
	    textEdit->setVisible(true);
            mainLayoutPolicy->insertItem(1, textEdit);
            m_List->setLayoutPosition(M::TopCenterPosition);
        } else if(textEdit->isOnDisplay()) {
            m_List->setFocus();
            qDebug() << "Textedit is NOT visible";
            textEdit->setVisible(false);
            mainLayoutPolicy->removeAt(1);
            textEdit->setText("");
        }
    }
}

QModelIndex
DisplayWidget::translateModelIndex(const QModelIndex &languageModelIndex)
{
    qDebug() << Q_FUNC_INFO;
    const QAbstractItemModel *sourceModel = languageModelIndex.model();
    QList<const MSortFilterProxyModel *> modelChain;
    const int maxDepth = 3;
    const QAbstractItemModel *m = m_List->itemModel();
    for (int depth = 0; depth < maxDepth; ++depth) {
        if (m == sourceModel) {
            break;
        }
        const MSortFilterProxyModel *proxyModel = 
            qobject_cast<const MSortFilterProxyModel *>(m);
        if (!proxyModel) {
            break;
        }
        modelChain.append(proxyModel);
        m = proxyModel->sourceModel();
    }
    if (m != sourceModel) {
        qWarning() << "original language model not found in proxy chain";
        return QModelIndex();
    }

    if (modelChain.isEmpty()) {
        // no proxy models in the way
        return languageModelIndex;
    }

    QModelIndex translatedIndex = languageModelIndex;
    for (int i = modelChain.count() - 1; i >= 0; --i) {
         const MSortFilterProxyModel *m = modelChain[i];
         translatedIndex = m->mapFromSource(translatedIndex);
    }

    return translatedIndex;
}
