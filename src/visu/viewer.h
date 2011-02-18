/*
 * viewer.h
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

#ifndef HEADER_GLVIEWER
#define HEADER_GLVIEWER

#include <QtGui>
#include <QGLViewer/qglviewer.h>

#include "../utils/simu_struct.h"
#include "molecule_visu.h"

class Viewer : public QGLViewer
{
    Q_OBJECT

public:
    Viewer(UnitFrame *_fr, int _sizeX, int _sizeY,
           int _sizeZ, int* fc_dims, int* dfc_dims,
           QColor fc_col, QColor dfc_col, QColor gc_col,
           QWidget *parent = 0);

protected :
    virtual void draw();
    virtual void init();
    virtual void animate();
    virtual QString helpString() const;

private:
    UnitFrame *fr;
    int sizeX;
    int sizeY;
    int sizeZ;

    MolVisu *molv;

private slots:
    void changeMolSize(int v);

    void showFCBox(int state);
    void showDFCBox(int state);
    void showGCBox(int state);

    void showFCBorder(int state);
    void showDFCBorder(int state);
    void showGCBorder(int state);

    void changeTransp(int t);
};

#endif
