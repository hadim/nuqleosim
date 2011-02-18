/*
 * mainwindow.cpp
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

#include "mainwindow.h"

#include "ui_aboutui.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    
    setupUi(this);
    
    // Init settings
    settings = new QSettings("NuQleoSim_Team", "NuQleoSim");

    bool dbExist = false;
    if(QFile::exists(settings->value("database/default_db").toString()))
    {
        dbExist = true;
    }
    

    if(!settings->value("hasSettings").toBool() || !dbExist)
    {
        makeDefaultConfig();
    }
    
    // Clean tabWidget
    while(tabWidget->currentIndex() != -1)
    {
        tabWidget->removeTab(tabWidget->currentIndex());
    }

    // Creating dataui
    dataui = new DataUI();
    tabWidget->addTab(dataui, QString(tr("Nucleolus database")));

    dataui->displayData(settings->value("database/default_db").toString(),
                        settings->value("database/default_schema").toString());

    // Creating simuui
    simuui = new SimuUI(dataui->getMolModel());
    tabWidget->addTab(simuui, QString(tr("Simulation")));
    simuui->loadMolList();

    // Creating anaui
    anaui = new AnaUI();
    tabWidget->addTab(anaui, QString(tr("Results")));
    
    // Init about window
    aboutWidget = new QDialog;
    Ui::AboutWidget ui;
    ui.setupUi(aboutWidget);

    // Init settings window
    setui = new SettingsUI(settings);

    // Connection whith SimuUi
    connect(simuui, SIGNAL(signal_simuIsDone(Results*)),
            anaui, SLOT(loadResults(Results*)));
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWidget->exec();
}

void MainWindow::on_actionOptions_triggered()
{
    setui->exec();
}

void MainWindow::makeDefaultConfig()
{
    settings->setValue("hasSettings", "true");

    settings->beginGroup("database");
    {
        QString db_path = QCoreApplication::applicationDirPath() +
            QDir::toNativeSeparators("/data/db.xml");

        QString schema_path = QCoreApplication::applicationDirPath() +
            QDir::toNativeSeparators("/data/db.xsd");
        
        settings->setValue("default_db", db_path);
        settings->setValue("default_schema", schema_path);
    }
    settings->endGroup();
}
