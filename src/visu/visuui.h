/*
 * visuui.h
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

#ifndef HEADER_VISUUI
#define HEADER_VISUUI

#include <QtGui>

#include "ui_visuui.h"
#include "linecaption.h"

#include "../utils/simu_struct.h"
#include "../utils/visu_struct.h"
#include "viewer.h"

class VisuUI : public QWidget, private Ui::VisuUI
{
    Q_OBJECT

public:
    VisuUI(QWidget *parent = 0);
    void setScene(UnitFrame *fr, int sizeX, int sizeY, int sizeZ,
                  int* fc_dims, int* dfc_dims);
    void setCaption(VisuCaption _caption);

protected:
    Viewer *viewer;
    void closeEvent(QCloseEvent *event);
    void closeWindow();
    bool visuIsRunning;

    VisuCaption capt;
    
public slots:
    void on_helpButton_clicked();
    
    void on_showFpsBox_stateChanged(int state);
    void on_showGridBox_stateChanged(int state);
    void on_showAxisBox_stateChanged(int state);

    void update();
    void setTitle(QString title);
    void setProgress(int p);

    void togglePlayButton();
    void on_playButton_clicked();
    void on_pauseButton_clicked();

    void setTranspSlide();

    void simuIsDone();

    void on_closeButton_clicked();

private:
    QColor fc_col;
    QColor dfc_col;
    QColor gc_col;

signals:
    void resumeSimu();
    void pauseSimu();
    void stopSimu();
    void changeSpeedSimu(int);
};

#endif
