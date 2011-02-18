/*
 * simuui.h
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

#ifndef HEADER_SIMUUI
#define HEADER_SIMUUI

#include <QtGui>
#include "../utils/definebug.h"

#include "ui_simuui.h"
#include "simuui.h"

#include "../handler/simuhandler.h"
#include "../datamodel/mol_struct.h"

#include "../results/results.h"

class SimuUI : public QWidget, private Ui::SimuUI
{
    Q_OBJECT

public:
    SimuUI(QList<QTreeWidgetItem *> _molModel, QWidget *parent = 0);

    void loadMolList();
    void setLaunchButtonEnabled(bool b);

private:
    SimuHandler *simuHand;
    QDialog *helpWidget;

    QList<QTreeWidgetItem *> molModel;
    QList<QTreeWidgetItem *> dataMolModel;

    MolStruct default_mol;
    QList<MolStruct> mols;

    void fillMolWidget(MolStruct mol, bool checkeded);
    int molInList(QString name);
    bool removeMolInList(QString name);

private slots:
    void on_launchButton_clicked();
    void on_helpButton_clicked();

    void on_molsWidget_clicked();
    void on_selectMol_clicked();

    void on_fcConcBox_valueChanged(double c);
    void on_dfcConcBox_valueChanged(double c);
    void on_gcConcBox_valueChanged(double c);

    void on_fcAccessBox_stateChanged(int state);
    void on_dfcAccessBox_stateChanged(int state);
    void on_gcAccessBox_stateChanged(int state);

    void on_movProbaBox_valueChanged(double c);

    void on_nameLabel_clicked();

    void simuIsDone(Results *resu);

signals:
    void signal_simuIsDone(Results *resu);

};


#endif
