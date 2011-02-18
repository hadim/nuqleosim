/*
 * visu_struct.h
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

#ifndef VISUSTRUCT_HEADER
#define VISUSTRUCT_HEADER
#include "../utils/simu_struct.h"
#include <string>

typedef struct ProtCaption
{
    std::string name;
    Color color;
}ProtCaption;

typedef struct RnaCaption
{
    int name;
    Color color;
}RnaCaption ;


typedef struct VisuCaption
{
    ProtCaption * proteins;
    int nproteins;
    RnaCaption * rnas;
    int nrnas;
    int* fc_dims;
    int* dfc_dims;
}VisuCaption;

#endif
