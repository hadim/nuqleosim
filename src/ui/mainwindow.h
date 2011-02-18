/*
 * mainwindow.h
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

#ifndef HEADER_MAINWINDOW
#define HEADER_MAINWINDOW

#include <QtGui>
#include "ui_mainwindow.h"

#include "dataui.h"
#include "simuui.h"
#include "anaui.h"
#include "../results/results.h"

#include "settingsui.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    DataUI *dataui;
    SimuUI *simuui;
    AnaUI *anaui;
    
    QDialog *aboutWidget;

    QSettings *settings;
    SettingsUI *setui;
    
    void makeDefaultConfig();

private slots:
    void on_actionAbout_triggered();
    void on_actionOptions_triggered();
};


#endif
