/*
 * dataui.h
 *
 * Copyright (c) 2010-2011 see AUTHORS
 */

/*
 * This file is part of nuqleosim.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef HEADER_DATAUI
#define HEADER_DATAUI

#include <QtGui>

#include "ui_dataui.h"

#include "../handler/datahandler.h"

class DataUI : public QWidget, private Ui::DataUI
{
    Q_OBJECT

public:
    DataUI(QWidget *parent = 0);
    bool displayData(QString fdatabase, QString fschema);
    QList<QTreeWidgetItem *> getMolModel();

private:
    DataHandler *dataHand;
    QList<QTreeWidgetItem *> expModel;
    QList<QTreeWidgetItem *> molModel;

    int molIndex;
    int expIndex;
    bool isMol;

    QWidget* infoWidget;
               
private slots:
    void on_listMolWidget_clicked();
    void on_listExpWidget_clicked();
    
    void on_addMolBut_clicked();
    void on_addExpBut_clicked();

    void molRemove(int index);
    void expRemove(int index);
    
};


#endif
