/*
 * anaui.h
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

#ifndef ANAUI_HEADER
#define ANAUI_HEADER

#include <QtGui>

#include "ui_anaui.h"

#include "../results/results.h"
#include "../results/plotui.h"
#include "../datamodel/resu_struct.h"

class AnaUI: public QWidget, private Ui::AnaUI
{
    Q_OBJECT
public:
    AnaUI(QWidget *parent = 0);

private:
    Results *resu;
    PlotUI *plot;

private slots:
    void loadResults(Results *resu);
    void on_genButton_clicked();

    void on_graphChoose_clicked();
    void on_tableChoose_clicked();

    void chechContentResultsBox();
    void closePlotWidget(int);

    void on_selectAllButton_clicked();
    void on_unselectAllButton_clicked();
};



#endif /* ANAUI_HEADER */
