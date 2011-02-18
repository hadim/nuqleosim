/*
 * plotui.h
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

#ifndef PLOTUI_HEADER
#define PLOTUI_HEADER

#include <QtGui>

#include "ui_plotui.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_text.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_panner.h>

#include "../datamodel/resu_struct.h"

class PlotUI: public QWidget, private Ui::PlotUI
{
    Q_OBJECT
public:
    PlotUI(Data &_data, QWidget *parent = 0);
    ~PlotUI();

private:
    Data data;

    void drawGraph();
    void generateTable();

    QTableWidget *tableWidget;
    QTableWidgetItem* getTableWidget(QString str);

    QwtPlot *wplot;
                   
private slots:
    void on_csvButton_clicked();
    void on_pngButton_clicked();
};

#endif /* PLOTUI_HEADER */
