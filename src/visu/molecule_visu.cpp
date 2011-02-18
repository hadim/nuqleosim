/*
 * molecule_visu.cpp
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

#include "molecule_visu.h"

using namespace qglviewer;

MolVisu::MolVisu(UnitFrame *_fr, int _sizeX, int _sizeY,int _sizeZ,
                 int* _fc_dims, int* _dfc_dims,
                 QColor _fc_col, QColor _dfc_col, QColor _gc_col)
{

    sizeX = _sizeX;
    sizeY = _sizeY;
    sizeZ = _sizeZ;
    
    fr = _fr;

    showFC = true;
    showDFC = true;
    showGC = true;

    showFCBorder = false;
    showDFCBorder = false;
    showGCBorder = false;

    fc_col = _fc_col;
    dfc_col = _dfc_col;
    gc_col = _gc_col;

    fc_dims = _fc_dims;
    dfc_dims = _dfc_dims;
    gc_dims = new int[3];
    gc_dims[0] = sizeX;
    gc_dims[1] = sizeY;
    gc_dims[2] = sizeZ;

    molSize = 0.5;

    transparency = 0.5;
}

void MolVisu::animate()
{
}

void MolVisu::draw()
{
    // Center on 0,0,0
    int shiftX = sizeX/2;
    int shiftY = sizeY/2;
    int shiftZ = sizeZ/2;

    int i;
    for(i = 0; i < sizeX * sizeY * sizeZ; i++)
    {
        // Show only selected compartments
        if( (fr[i].compartment == FC_comp && showFC) ||
            (fr[i].compartment == DFC_comp && showDFC) ||
            (fr[i].compartment == GC_comp && showGC) )
        {
            if(fr[i].flag == protein_flag || fr[i].flag == rna_flag)
            {
                float size = molSize*4;
                if(fr[i].flag == rna_flag)
                {
                    size *= 0.6;
                }
                else
                {
                    size *= 1;
                }

                glPushMatrix();
                {
                    glColor3ub(fr[i].color.r, fr[i].color.g, fr[i].color.b);
                    glTranslatef(fr[i].pos.x - shiftX,
                                 fr[i].pos.y - shiftY,
                                 fr[i].pos.z - shiftZ);
                    drawSphere(size, 10, 10);
                }
                glPopMatrix();
            }
        }
    }

    // Draw FC, DFC and GC borders
    if(showFCBorder)
        drawBorder(fc_col, fc_dims, transparency);
    if(showDFCBorder)
        drawBorder(dfc_col, dfc_dims, transparency);
    if(showGCBorder)
        drawBorder(gc_col, gc_dims, transparency);
}

void MolVisu::drawSphere(double r, int lats, int longs)
{
    glScalef(r/4, r/4, r/4);
    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);
    
        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);
    
        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
    
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

void MolVisu::changeMolSize(int v)
{
    molSize = v / 100.0;
}

void MolVisu::setShowFC(bool show)
{
    showFC = show;
}

void MolVisu::setShowDFC(bool show)
{
    showDFC = show;
}

void MolVisu::setShowGC(bool show)
{
    showGC = show;
}

void MolVisu::setShowFCBorder(bool show)
{
    showFCBorder = show;
}

void MolVisu::setShowDFCBorder(bool show)
{
    showDFCBorder = show;
}

void MolVisu::setShowGCBorder(bool show)
{
    showGCBorder = show;
}

void MolVisu::drawBorder(QColor col, int* dims, float transp)
{
    int r, g, b;
    col.getRgb(&r, &g, &b);

    int x = dims[0] / 2;
    int y = dims[1] / 2;
    int z = dims[2] / 2;

    glBegin(GL_QUADS);{

        glColor4f(r/255.0, g/255.0, b/255.0, transp);

        glVertex3d(1*x,1*y,1*z);
        glVertex3d(1*x,1*y,-1*z);
        glVertex3d(-1*x,1*y,-1*z);
        glVertex3d(-1*x,1*y,1*z);

        glVertex3d(1*x,-1*y,1*z);
        glVertex3d(1*x,-1*y,-1*z);
        glVertex3d(1*x,1*y,-1*z);
        glVertex3d(1*x,1*y,1*z);

        glVertex3d(-1*x,-1*y,1*z);
        glVertex3d(-1*x,-1*y,-1*z);
        glVertex3d(1*x,-1*y,-1*z);
        glVertex3d(1*x,-1*y,1*z);

        glVertex3d(-1*x,1*y,1*z);
        glVertex3d(-1*x,1*y,-1*z);
        glVertex3d(-1*x,-1*y,-1*z);
        glVertex3d(-1*x,-1*y,1*z);

        glVertex3d(1*x,1*y,-1*z);
        glVertex3d(1*x,-1*y,-1*z);
        glVertex3d(-1*x,-1*y,-1*z);
        glVertex3d(-1*x,1*y,-1*z);

        glVertex3d(1*x,-1*y,1*z);
        glVertex3d(1*x,1*y,1*z);
        glVertex3d(-1*x,1*y,1*z);
        glVertex3d(-1*x,-1*y,1*z);

    }glEnd();
}

void MolVisu::setTransp(float t)
{
    transparency = t;
}
