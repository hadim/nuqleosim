/*
 * rna_struct.h
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

#ifndef RNA_STRUCT_H
#define RNA_STRUCT_H

#include "../utils/simu_struct.h"

typedef struct Rna_struct
  {
    char type;//P protein R rna
    bool FC_access; 
    bool DFC_access;
    bool GC_access;
    bool ext_access;
    Flag flag;//je le remplirai
    Color color;//je le remplirai
  }Rna_struct;
#endif
