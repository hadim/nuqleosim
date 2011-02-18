/*
 * plotui.cpp
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

#include "plotui.h"

PlotUI::PlotUI(Data &_data, QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    data = _data;

    if(data.isGraph)
        drawGraph();
    else
        generateTable();

}

PlotUI::~PlotUI()
{
}

void PlotUI::drawGraph()
{
    // Setup the plot
    wplot = new QwtPlot(QwtText(data.title));

    QwtLegend *legend = new QwtLegend ;
    legend->setItemMode(QwtLegend::CheckableItem);
    wplot->insertLegend(legend, QwtPlot::RightLegend);

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->attach(wplot);

    QwtPlotPanner *panner = new QwtPlotPanner(wplot->canvas());
    panner->setAxisEnabled(QwtPlot::yRight, false);
    panner->setMouseButton(Qt::MidButton);

    // Give data to the plot
    QColor color[10] = { Qt::red, Qt::black, Qt::green,
                         Qt::magenta, Qt::cyan, Qt::yellow,
                         Qt::blue, Qt::white, Qt::darkGreen, Qt::darkBlue };
    
    // Create time axis
    double *time = new double[data.nbPlots];
    for (int i = 1; i < data.nbPlots; i++)
    {
        time[i] = (double)i;
    }

    // Create curves
    int i = 0;
    int mol = 0;
    foreach(QString str, data.data.keys())
    {
        QwtText title(str);
        title.setColor(color[mol]);
        
        QwtPlotCurve *curve = new QwtPlotCurve(title);
        double *conc = new double[data.nbPlots];

        foreach(int v, data.data[str])
        {
            conc[i] = (double)v;
            i++;
        }
        curve->setData(time, conc, data.nbPlots);
        curve->attach(wplot);
        curve->setPen(QPen(color[mol]));

        i = 0;
        mol++;
    }

    wplot->replot();

    graphContainer->addWidget(wplot);

    // Allow export at csv and png
    csvButton->setEnabled(true);
    pngButton->setEnabled(true);
}

void PlotUI::generateTable()
{
    // Setup the table
    tableWidget = new QTableWidget();
        
    tableWidget->setRowCount(data.data.size() + 1);
    tableWidget->setColumnCount(data.nbPlots + 1);

    tableWidget->verticalHeader()->hide();
    tableWidget->horizontalHeader()->hide();
    
    // Fill the table
    tableWidget->setUpdatesEnabled(false);

    // Fill time line
    tableWidget->setItem(0, 0, getTableWidget(tr("Iteration")));

    for (int i = 1; i < data.nbPlots + 1; i++)
    {
        tableWidget->setItem(0, i, getTableWidget(QString::number(i)));
    }

    int row = 1;
    int col = 1;
    foreach(QString str, data.data.keys())
    {
        tableWidget->setItem(row, 0, getTableWidget(str));
        foreach(int v, data.data[str])
        {
            tableWidget->setItem(row,col,getTableWidget(QString::number(v)));
            col ++;
        }
        row++;
        col = 1;
    }
    
    tableWidget->setUpdatesEnabled(true);
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();

    graphContainer->addWidget(tableWidget);

    // Allow export at csv
    csvButton->setEnabled(true);
}

QTableWidgetItem* PlotUI::getTableWidget(QString str)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    item->setText(str);

    return item;
}

void PlotUI::on_csvButton_clicked()
{
    QString fname = QFileDialog::getSaveFileName(this, tr("Save File"));

    // Write data to csv
    QFile f(fname);

    if(f.open(QIODevice::WriteOnly))
    {
        QTextStream ts(&f);
        QStringList strList;
        
        for(int r = 0; r < tableWidget->rowCount(); r++)
        {
            strList.clear();
            for( int c = 0; c < tableWidget->columnCount() - 1; c++)
            {
                strList << "\"" + tableWidget->item(r, c)->text() + "\"";
            }
            ts << strList.join( "," )+"\n";
        }
        f.close();
    }

    msgBar->setText(QString(tr("Data have been correctly saved to %1")).arg(fname));

}

void PlotUI::on_pngButton_clicked()
{
    QString fname = QFileDialog::getSaveFileName(this, tr("Save File"));

    QwtPlotPrintFilter filter;
    // int options = QwtPlotPrintFilter::PrintAll;
    // int options = ~QwtPlotPrintFilter::PrintBackground;
    int options = QwtPlotPrintFilter::PrintFrameWithScales;
    options |= QwtPlotPrintFilter::PrintBackground;
    filter.setOptions(options);

    QPixmap pixmap= QPixmap::grabWidget(wplot);

    QString message;
    if(pixmap.save(fname, "png"))
        message = tr("Data have been correctly saved to %1");
    else
        message = tr("There was a problem saving plot at %1");

    msgBar->setText(message.arg(fname));

}
