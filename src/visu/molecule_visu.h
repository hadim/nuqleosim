/*
 * molecule_visu.h
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

#ifndef HEADER_MOLECULE_VISU
#define HEADER_MOLECULE_VISU

#include <QtGui>
#include <QGLViewer/qglviewer.h>

#include "../utils/simu_struct.h"
#include <math.h>

class MolVisu
{
public :
    MolVisu(UnitFrame *_fr, int _sizeX, int _sizeY,int _sizeZ,
            int* fc_dims, int* dfc_dims,
            QColor fc_col, QColor dfc_col, QColor gc_col);

    void draw();
    void animate();

    void changeMolSize(int v);

    void setShowFC(bool show);
    void setShowDFC(bool show);
    void setShowGC(bool show);

    void setShowFCBorder(bool show);
    void setShowDFCBorder(bool show);
    void setShowGCBorder(bool show);

    void setTransp(float t);

protected:
    UnitFrame *fr;
    int sizeX;
    int sizeY;
    int sizeZ;

    bool showFC;
    bool showDFC;
    bool showGC;

    bool showFCBorder;
    bool showDFCBorder;
    bool showGCBorder;

    QColor fc_col;
    QColor dfc_col;
    QColor gc_col;

    int* fc_dims;
    int* dfc_dims;
    int* gc_dims;

    float transparency;

    float molSize;

    void drawSphere(double r, int lats, int longs);
    void drawBorder(QColor col, int* dims, float transp);

};

#endif
