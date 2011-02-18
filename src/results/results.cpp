/*
 * results.cpp
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

#include "results.h"

Results::Results(Resu_struct *_resu)
{
    resu = _resu;
}

QString Results::to_str()
{    
    return "coucou";
}

Data Results::getData(QMap < QString, bool > dataToPlot)
{
    Data data;
    data.nbPlots = resu->nbPlots;

    // Fill gc concentration
    if(dataToPlot["gcrna1"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->gc_rna1[i]);
        }
        data.data["GC RNA 1"] = conc;
    }

    if(dataToPlot["gcrna2"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->gc_rna2[i]);
        }
        data.data["GC RNA 2"] = conc;
    }

    if(dataToPlot["gcrna3"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->gc_rna3[i]);
        }
        data.data["GC RNA 3"] = conc;
    }

    // Fill dfc concentration
    if(dataToPlot["dfcrna1"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->dfc_rna1[i]);
        }
        data.data["DFC RNA 1"] = conc;
    }

    if(dataToPlot["dfcrna2"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->dfc_rna2[i]);
        }
        data.data["DFC RNA 2"] = conc;
    }

    if(dataToPlot["dfcrna3"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->dfc_rna3[i]);
        }
        data.data["DFC RNA 3"] = conc;
    }

    // Fill fc concentration
    if(dataToPlot["fcrna1"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->fc_rna1[i]);
        }
        data.data["FC RNA 1"] = conc;
    }

    if(dataToPlot["fcrna2"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->fc_rna2[i]);
        }
        data.data["FC RNA 2"] = conc;
    }

    if(dataToPlot["fcrna3"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->fc_rna3[i]);
        }
        data.data["FC RNA 3"] = conc;
    }

    // Fill out rna concentration
    if(dataToPlot["rnaout"])
    {
        QList <int> conc;
        for (int i = 0; i < resu->nbPlots; i++)
        {
            conc.append(resu->out_rna[i]);
        }
        data.data["OUT RNA"] = conc;
    }

    return data;
}

