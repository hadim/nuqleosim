/*
 * resu_struct.h
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

#ifndef RESU_STRUCT_H
#define RESU_STRUCT_H

typedef struct Resu_struct
{
    int nbPlots;
    int stepSize;

    int * gc_rna1;
    int * gc_rna2;
    int * gc_rna3;

    int * dfc_rna1;
    int * dfc_rna2;
    int * dfc_rna3;

    int * fc_rna1;
    int * fc_rna2;
    int * fc_rna3;
    
    int * out_rna;

} Resu_struct;

typedef struct Data
{
    bool isGraph;
    QString title;
    QMap< QString, QList<int> > data;
    int nbPlots;

} Data;

#endif

