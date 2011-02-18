/*
 * dataui.cpp
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

#include "dataui.h"

DataUI::DataUI(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    // Resize widget
    singleDataWidget->resize(width()*0.85, widget->height());

    // Set current index
    molIndex = -1;
    expIndex = -1;

    infoWidget = new QWidget();
}

bool DataUI::displayData(QString fdatabase, QString fschema)
{
    // Load database
    dataHand = new DataHandler(fdatabase, fschema);
    molModel = dataHand->getMolModel();
    expModel = dataHand->getExpModel();

    // Signal connection
    connect(dataHand, SIGNAL(signal_molRemove(int)),
            this, SLOT(molRemove(int)));
    connect(dataHand, SIGNAL(signal_expRemove(int)),
            this, SLOT(expRemove(int)));

    // Set model
    listMolWidget->setColumnCount(2);
    listMolWidget->insertTopLevelItems(0, molModel);

    listExpWidget->setColumnCount(2);
    listExpWidget->insertTopLevelItems(0, expModel);

    return true;
}

void DataUI::on_listMolWidget_clicked()
{
    QTreeWidgetItem *current = listMolWidget->currentItem();
    int index = current->text(0).toInt();
    
    if(index != molIndex || isMol == false)
    {
        isMol = true;
        molIndex = index;

        // Hide welcomeLabel
        welcomeLabel->hide();

        if(infoWidget != NULL){
            delete infoWidget;
        }

        infoWidget = dataHand->getMolWidget(molIndex);
        infoWidget->setParent(singleDataWidget);

        singleDataWidget->layout()->addWidget(infoWidget);
        
        listExpWidget->setCurrentItem(0);
        
        // Show info
        singleDataWidget->show();
    }
}

void DataUI::on_listExpWidget_clicked()
{
    QTreeWidgetItem * current = listExpWidget->currentItem();
    int index = current->text(0).toInt();
    
    if(index != expIndex || isMol == true)
    {
        isMol = false;
        expIndex = index;

        // Hide welcomeLabel
        welcomeLabel->hide();

        if(infoWidget != NULL){
            delete infoWidget;
        }

        infoWidget = dataHand->getExpWidget(current->text(0).toInt());
        infoWidget->setParent(singleDataWidget);

        singleDataWidget->layout()->addWidget(infoWidget);
        
        listMolWidget->setCurrentItem(0);

        // Show info
        singleDataWidget->show();
    }
}

void DataUI::molRemove(int index)
{
    molModel.removeAt(index);
    delete listMolWidget->currentItem();

    // TODO: fix bug seg fault when call this function
    //on_listMolWidget_clicked();
}

void DataUI::expRemove(int index)
{
    expModel.removeAt(index);
    delete listExpWidget->currentItem();

    // TODO: fix bug seg fault when call this function
    //on_listExpWidget_clicked();
}

void DataUI::on_addMolBut_clicked()
{
    QTreeWidgetItem* item = dataHand->molAdd();
    listMolWidget->addTopLevelItem(item);
    molModel.append(item);
    
    // TODO: fix bug seg fault when call this function
    //listMolWidget->setCurrentItem(item);
    //on_listMolWidget_clicked();
}

void DataUI::on_addExpBut_clicked()
{
    QTreeWidgetItem* item = dataHand->expAdd();
    listExpWidget->addTopLevelItem(item);
    expModel.append(item);
    
    // TODO: fix bug seg fault when call this function
    //listExpWidget->setCurrentItem(item);
    //on_listExpWidget_clicked();
}

QList<QTreeWidgetItem *> DataUI::getMolModel()
{
    return molModel;
}
