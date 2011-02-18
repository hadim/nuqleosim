/*
 * visuui.cpp
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

#include "visuui.h"

VisuUI::VisuUI(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
        
    // Show all compartments by default
    showFCBox->setCheckState(Qt::Checked);
    showDFCBox->setCheckState(Qt::Checked);
    showGCBox->setCheckState(Qt::Checked);

    showFCBorderBox->setCheckState(Qt::Unchecked);
    showDFCBorderBox->setCheckState(Qt::Unchecked);
    showGCBorderBox->setCheckState(Qt::Unchecked);

    // Enable interface button
    pauseButton->setEnabled(true);
    playButton->setEnabled(true);
    progressBar->setValue(0);
    progressBar->setEnabled(true);

    // Set color for border
    fc_col = QColor(255, 0, 0);
    dfc_col = QColor(0, 255, 0);
    gc_col = QColor(0, 0, 255);
}

void VisuUI::setScene(UnitFrame *fr, int sizeX, int sizeY, int sizeZ,
                      int* fc_dims, int* dfc_dims)
{
    viewer = new Viewer(fr, sizeX, sizeY, sizeZ,
                        fc_dims, dfc_dims, fc_col,
                        dfc_col, gc_col);

    containerVisu->layout()->addWidget(viewer);

    visuIsRunning = true;

    // Connect options with viewer
    connect(showFCBox, SIGNAL(stateChanged(int )), 
            viewer, SLOT(showFCBox(int)));
    connect(showDFCBox, SIGNAL(stateChanged(int )), 
            viewer, SLOT(showDFCBox(int)));
    connect(showGCBox, SIGNAL(stateChanged(int )), 
            viewer, SLOT(showGCBox(int)));

    connect(showFCBorderBox, SIGNAL(stateChanged(int )), 
            viewer, SLOT(showFCBorder(int)));
    connect(showDFCBorderBox, SIGNAL(stateChanged(int )), 
            viewer, SLOT(showDFCBorder(int)));
    connect(showGCBorderBox, SIGNAL(stateChanged(int )), 
            viewer, SLOT(showGCBorder(int)));

    connect(showFCBorderBox, SIGNAL(stateChanged(int)), 
            this, SLOT(setTranspSlide()));
    connect(showDFCBorderBox, SIGNAL(stateChanged(int)), 
            this, SLOT(setTranspSlide()));
    connect(showGCBorderBox, SIGNAL(stateChanged(int)), 
            this, SLOT(setTranspSlide()));

    setTranspSlide();
}

void VisuUI::on_helpButton_clicked()
{
    viewer->help();
}

void VisuUI::on_showFpsBox_stateChanged(int state)
{
    viewer->toggleFPSIsDisplayed();
}

void VisuUI::on_showGridBox_stateChanged(int state)
{
    viewer->toggleGridIsDrawn();
}

void VisuUI::on_showAxisBox_stateChanged(int state)
{
    viewer->toggleAxisIsDrawn();
}

void VisuUI::update()
{
    viewer->updateGL();
}

void VisuUI::setTitle(QString title)
{
    messageBar->setText(title);
}

void VisuUI::setProgress(int p)
{
    progressBar->show();
    progressBar->setValue(p);
}

void VisuUI::togglePlayButton()
{
    if(playButton->isVisibleTo(this) && pauseButton->isVisibleTo(this))
        playButton->hide();

    else if(playButton->isVisibleTo(this))
    {
        playButton->hide();
        pauseButton->show();
    }
    else if(pauseButton->isVisibleTo(this))
    {
        pauseButton->hide();
        playButton->show();
    }
}

void VisuUI::on_playButton_clicked()
{
    // Resume simu
    emit resumeSimu();
    togglePlayButton();
}
 
void VisuUI::on_pauseButton_clicked()
{
    // Pause simu
    emit pauseSimu();
    togglePlayButton();
}

void VisuUI::simuIsDone()
{
    pauseButton->setEnabled(false);
    playButton->setEnabled(false);
    //progressBar->setValue(0);
}

void VisuUI::on_closeButton_clicked()
{
    closeWindow();
}

void VisuUI::closeEvent(QCloseEvent *event)
{
     closeWindow();
}

void VisuUI::closeWindow()
{
    if(visuIsRunning)
    {
        emit stopSimu();
    }
    visuIsRunning = false;
}

void VisuUI::setCaption(VisuCaption _caption)
{
    capt = _caption;
    
    // Proteins captions
    QLabel *l = new QLabel(tr("Proteins colors : "));
    containerCaption->addWidget(l);

    int i;
    for(i = 0; i < capt.nproteins; i++)
    {
        QString name = QString::fromStdString(capt.proteins[i].name);
        LineCaption *line = new LineCaption(name,
                                            capt.proteins[i].color.r,
                                            capt.proteins[i].color.g,
                                            capt.proteins[i].color.b );
        containerCaption->addWidget(line);
    }

    // RNAs captions
    l = new QLabel(tr("RNAs colors : "));
    containerCaption->addWidget(l);

    QString name;
    LineCaption *line;

    name = tr("Maturation level 1");
    line = new LineCaption(name,
                           capt.rnas[0].color.r,
                           capt.rnas[0].color.g,
                           capt.rnas[0].color.b );
    containerCaption->addWidget(line);

    name = tr("Maturation level 2");
    line = new LineCaption(name,
                           capt.rnas[1].color.r,
                           capt.rnas[1].color.g,
                           capt.rnas[1].color.b );
    containerCaption->addWidget(line);

    name = tr("Maturation level 3");
    line = new LineCaption(name,
                           capt.rnas[2].color.r,
                           capt.rnas[2].color.g,
                           capt.rnas[2].color.b );
    containerCaption->addWidget(line);

    // Comp captions
    l = new QLabel(tr("Compartments colors"));
    containerCaption->addWidget(l);

    int r, g, b;

    fc_col.getRgb(&r, &g, &b);
    name = tr("FC");
    line = new LineCaption(name,
                           r, g, b);
    containerCaption->addWidget(line);

    dfc_col.getRgb(&r, &g, &b);
    name = tr("DFC");
    line = new LineCaption(name,
                           r, g, b);
    containerCaption->addWidget(line);

    gc_col.getRgb(&r, &g, &b);
    name = tr("GC");
    line = new LineCaption(name,
                           r, g, b);
    containerCaption->addWidget(line);

    containerCaption->addStretch();

    // Connect some options with visu
    connect(sizeSlider, SIGNAL(valueChanged(int)),
            viewer, SLOT(changeMolSize(int)));
    connect(speedSlider, SIGNAL(valueChanged(int)),
            this, SIGNAL(changeSpeedSimu(int)));
    connect(transpSlider, SIGNAL(valueChanged(int)),
            viewer, SLOT(changeTransp(int)));
}

void VisuUI::setTranspSlide()
{
    if(showFCBorderBox->checkState() == Qt::Unchecked &&
       showDFCBorderBox->checkState() == Qt::Unchecked &&
       showGCBorderBox->checkState() == Qt::Unchecked )
    {
        transpSlider->setEnabled(false);
        transpLabel->setEnabled(false);
    }
    else
    {
        transpSlider->setEnabled(true);
        transpLabel->setEnabled(true);
    }
}
