/*
 * viewer.cpp
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

#include "viewer.h"

using namespace qglviewer;

Viewer::Viewer(UnitFrame *_fr, int _sizeX, int _sizeY,
               int _sizeZ, int* fc_dims, int* dfc_dims,
               QColor fc_col, QColor dfc_col, QColor gc_col,
               QWidget *parent)
{
    sizeX = _sizeX;
    sizeY = _sizeY;
    sizeZ = _sizeZ;

    fr = _fr;

    molv = new MolVisu(fr, sizeX, sizeY, sizeZ,
                       fc_dims, dfc_dims,
                       fc_col, dfc_col, gc_col);
}

void Viewer::draw()
{
    molv->draw();
}

void Viewer::init()
{
    //restoreStateFromFile();
    
    int maxSide;
    if(sizeX < sizeY)
        maxSide = sizeY;
    else
        maxSide = sizeX;

    if(maxSide < sizeZ)
        maxSide = sizeZ;

    // QGLViewer init
    //setGridIsDrawn();
    camera()->setPosition(Vec(0, 0, maxSide * 2.2));
    setSceneRadius(maxSide * 1.1);	
    camera()->centerScene();

    // Light default parameters
	const GLfloat light_ambient[4]  = { 0.1f, 0.1f, 0.1f, 1.0f };
    const GLfloat light_diffuse[4]  = { 0.5f, 0.5f, 0.5f, 1.0f };
    const GLfloat light_position[4] = { 45.0f, 0.0f, 2.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
 	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    // Light setup
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    
    //Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

void Viewer::animate()
{
    molv->animate();
}

QString Viewer::helpString() const
{
    QString text("<h2> NuQleoSim Viewer</h2>");
    text += "<b>Print some help here</b>";
    return text;
}

void Viewer::changeMolSize(int v)
{
    molv->changeMolSize(v);
    updateGL();
}

void Viewer::showFCBox(int state)
{
    if(state == Qt::Checked)
        molv->setShowFC(true);
    else
        molv->setShowFC(false);
    updateGL();
}

void Viewer::showDFCBox(int state)
{
    if(state == Qt::Checked)
        molv->setShowDFC(true);
    else
        molv->setShowDFC(false);
    updateGL();
}
void Viewer::showGCBox(int state)
{
    if(state == Qt::Checked)
        molv->setShowGC(true);
    else
        molv->setShowGC(false);
    updateGL();
}

void Viewer::showFCBorder(int state)
{
    if(state == Qt::Checked)
        molv->setShowFCBorder(true);
    else
        molv->setShowFCBorder(false);
    updateGL();
}

void Viewer::showDFCBorder(int state)
{
    if(state == Qt::Checked)
        molv->setShowDFCBorder(true);
    else
        molv->setShowDFCBorder(false);
    updateGL();
}

void Viewer::showGCBorder(int state)
{
    if(state == Qt::Checked)
        molv->setShowGCBorder(true);
    else
        molv->setShowGCBorder(false);
    updateGL();
}

void Viewer::changeTransp(int t)
{
    molv->setTransp(t / 100.0);
    updateGL();
}
