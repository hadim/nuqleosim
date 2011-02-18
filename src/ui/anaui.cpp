/*
 * anaui.cpp
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

#include "anaui.h"

AnaUI::AnaUI(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    // Hide results widget
    resuWidget->hide();
    noResLabel->show();
}

void AnaUI::loadResults(Results *_resu)
{
    resu = _resu;

    tabWidget->resize(tabWidget->width(), resuWidget->height()/2);

    // Display a nice message
    msgBar->setText("Setup how do you want to see your results and then generate them");

    // Setup widget
    resuWidget->show();
    noResLabel->hide();

    //Setup options
    graphChoose->setChecked(true);
    tableChoose->setChecked(false);
    
    on_graphChoose_clicked();
    chechContentResultsBox();

    // Connect content results
    connect(gcResBox, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(fcResBox, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(dfcResBox, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));

    connect(gcrna1, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(gcrna2, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(gcrna3, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));

    connect(dfcrna1, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(dfcrna2, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(dfcrna3, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));

    connect(fcrna1, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(fcrna2, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));
    connect(fcrna3, SIGNAL(clicked()), this, SLOT(chechContentResultsBox()));

    // Connect close tab
    connect(tabWidget, SIGNAL(tabCloseRequested(int)),
                              this, SLOT(closePlotWidget(int)));
}

void AnaUI::on_graphChoose_clicked()
{
    if(graphChoose->isChecked())
    {
        graphOptionsWidget->setEnabled(true);
        tableOptionsWidget->setEnabled(false);
    }
    else
    {
        graphOptionsWidget->setEnabled(false);
        tableOptionsWidget->setEnabled(true);
    }
}

void AnaUI::on_tableChoose_clicked()
{
    if(tableChoose->isChecked())
    {
        graphOptionsWidget->setEnabled(false);
        tableOptionsWidget->setEnabled(true);
    }
    else
    {
        graphOptionsWidget->setEnabled(true);
        tableOptionsWidget->setEnabled(false);
    }
}

void AnaUI::chechContentResultsBox()
{
    // GC results
    if(gcResBox->isChecked())
    {
        gcrnaBox->setEnabled(true);
    }
    else
    {
        gcrnaBox->setEnabled(false);
    }
    
    // DFC results
    if(dfcResBox->isChecked())
    {
        dfcrnaBox->setEnabled(true);
    }
    else
    {
        dfcrnaBox->setEnabled(false);
    }

    // FC results
    if(fcResBox->isChecked())
    {
        fcrnaBox->setEnabled(true);
    }
    else
    {
        fcrnaBox->setEnabled(false);
    }
}

void AnaUI::on_genButton_clicked()
{
    // Build data to plot
    QMap < QString, bool > dataToPlot;

    if(gcResBox->isChecked())
    {
        dataToPlot["gcrna1"] = gcrna1->isChecked();
        dataToPlot["gcrna2"] = gcrna2->isChecked();
        dataToPlot["gcrna3"] = gcrna3->isChecked();
    }

    if(dfcResBox->isChecked())
    {
        dataToPlot["dfcrna1"] = dfcrna1->isChecked();
        dataToPlot["dfcrna2"] = dfcrna2->isChecked();
        dataToPlot["dfcrna3"] = dfcrna3->isChecked();
    }

    if(fcResBox->isChecked())
    {
        dataToPlot["fcrna1"] = fcrna1->isChecked();
        dataToPlot["fcrna2"] = fcrna2->isChecked();
        dataToPlot["fcrna3"] = fcrna3->isChecked();
    }

    dataToPlot["rnaout"] = rnaout->isChecked();
    
    Data data = resu->getData(dataToPlot);
    data.title = graphTitle->text();
    data.isGraph = graphChoose->isChecked();

    if(data.data.size() == 0)
    {
        QMessageBox::warning(this,
                             tr("No data to plot !"),
                             tr("You have to select at least one type "
                                "concentration to display. "),
                             QMessageBox::Close,
                             QMessageBox::Close);
    }
    
    else{
        // Build and insert new graph or table in tabWidget
        plot = new PlotUI(data);
        tabWidget->addTab(plot, QString(""));
        tabWidget->setCurrentWidget(plot);
    }
}

void AnaUI::closePlotWidget(int index)
{
    tabWidget->removeTab(index);
}

void AnaUI::on_selectAllButton_clicked()
{
    gcResBox->setChecked(true);
    gcrna1->setChecked(true);
    gcrna2->setChecked(true);
    gcrna3->setChecked(true);
    
    dfcResBox->setChecked(true);
    dfcrna1->setChecked(true);
    dfcrna2->setChecked(true);
    dfcrna3->setChecked(true);

    fcResBox->setChecked(true);
    fcrna1->setChecked(true);
    fcrna2->setChecked(true);
    fcrna3->setChecked(true);
    
    chechContentResultsBox();
}

void AnaUI::on_unselectAllButton_clicked()
{
    gcResBox->setChecked(false);
    gcrna1->setChecked(false);
    gcrna2->setChecked(false);
    gcrna3->setChecked(false);

    dfcResBox->setChecked(false);
    dfcrna1->setChecked(false);
    dfcrna2->setChecked(false);
    dfcrna3->setChecked(false);

    fcResBox->setChecked(false);
    fcrna1->setChecked(false);
    fcrna2->setChecked(false);
    fcrna3->setChecked(false);

    chechContentResultsBox();
}

