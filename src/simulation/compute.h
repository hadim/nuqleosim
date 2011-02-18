/*
 * compute.h
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

#ifndef COMPUTE_HEADER
#define COMPUTE_HEADER

#include "../paramaccess.h"

#include "../utils/simu_struct.h"
#include "../utils/visu_struct.h"

#include "../datamodel/mol_struct.h"
#include "../datamodel/rna_struct.h"
#include "../datamodel/resu_struct.h"

#include <vector>

class Compute : public QThread
{
    Q_OBJECT

    protected:
    void run();
    
    UnitFrame * environment;
    int  length;
    int height;
    int width;
    int nbColonies;
    std::vector<MolStruct> colonies;
    int nbColoniesRna;
    Rna_struct * coloniesRna;
    Resu_struct * results;
    virtual void step(int nbIterations) = 0;
    virtual void init_results()=0;
    int cpt_iter;
    int stepNb;
    int iterTot;
    bool doSimu;
    bool stopFlag;
    int speedSimu;



public:
    virtual void init(ParamAccess *parameters) = 0;  
    void setStepNb(int _stepNb);

    virtual VisuCaption get_caption()=0;

    UnitFrame * getEnv();
    Resu_struct * get_results();
    void pauseSimu();
    void resumeSimu();
    void setStopFlag(bool b);

signals:
    void stepDone();
    void progress(int p);

private slots:
    void setSpeedSimu(int s);
};

#endif
