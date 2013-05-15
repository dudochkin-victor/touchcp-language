#include "mlistfilter.h"
#include <mtextedit.h>

MListFilter::MListFilter(MList *){}
MListFilter::~MListFilter(){}
void MListFilter::setEnabled(bool){}
bool MListFilter::enabled(){}
MTextEdit *MListFilter::editor() const {return new MTextEdit();}

    /*

    MSortFilterProxyModel *proxy() const;
*/
 void MListFilter::setFilterRole(int){}
/*
    int filterRole() const;

    void keyPressEvent(QKeyEvent *event);
*/
void MListFilter::setFilterMode(MListFilter::FilterMode mode){}
/*
    MListFilter::FilterMode filterMode() const;
    void editorTextChanged();
*/
