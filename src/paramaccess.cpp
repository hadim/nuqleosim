/*
 * paramaccess.cpp
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

#include "paramaccess.h"

ParamAccess::ParamAccess()
{
}

std::vector<MolStruct> ParamAccess::getMols()
{
    return mols.toVector().toStdVector();
}

int ParamAccess::getLength()
{
    return length;
}

int ParamAccess::getHeight()
{
    return height;
}

int ParamAccess::getWidth()
{
    return width;
}

int ParamAccess::getIter()
{
    return iter;
}

int ParamAccess::getNmeasure()
{
    return nmeasure;
}

void ParamAccess::setMols(QList<MolStruct> _mols)
{
    mols = _mols;
}

void ParamAccess::setLength(int _length)
{
    length = _length;
}

void ParamAccess::setHeight(int _height)
{
    height = _height;
}

void ParamAccess::setWidth(int _width)
{
    width = _width;
}

void ParamAccess::setIter(int _iter)
{
    iter = _iter;
}

void ParamAccess::setNmeasure(int _nmeasure)
{
    nmeasure = _nmeasure;
}

QString ParamAccess::to_str()
{
    QString ret = "";

    ret += "************\n\n";

    ret += "length : ";
    ret += QString::number(length);
    ret += "\n";

    ret += "height : ";
    ret += QString::number(height);
    ret += "\n";

    ret += "width : ";
    ret += QString::number(width);
    ret += "\n";

    ret += "iteration : ";
    ret += QString::number(iter);
    ret += "\n\n";

    foreach(MolStruct mol, mols)
    {
        ret += ". name : ";
        ret += QString::fromStdString(mol.name);
        ret += "\n";

        ret += "FC pourcentage : ";
        ret += QString::number(mol.FC_pourcentage);
        ret += " | accessible : ";
        ret += QString(mol.FC_access?tr("yes"):tr("no"));
        ret += "\n";

        ret += "DFC pourcentage : ";
        ret += QString::number(mol.DFC_pourcentage);
        ret += " | accessible : ";
        ret += QString(mol.DFC_access?tr("yes"):tr("no"));
        ret += "\n";

        ret += "GC pourcentage : ";
        ret += QString::number(mol.GC_pourcentage);
        ret += " | accessible : ";
        ret += QString(mol.GC_access?tr("yes"):tr("no"));
        ret += "\n";

        ret += "Move probability : ";
        ret += QString::number(mol.mov_proba);

        ret += "\n\n";
    }
    
    ret += "\n************";

    return ret;
}
