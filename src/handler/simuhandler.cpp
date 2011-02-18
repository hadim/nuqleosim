/*
 * simuhandler.cpp
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

#include "simuhandler.h"

SimuHandler::SimuHandler()
{

    // Create paramSimu object which contains
    // all informations to compute the simulation
    paramSimu = new ParamAccess();
    
    iterByStep = 10;
    isVisu = true;
}

void SimuHandler::setParameters(int lengthBox, int widthBox,
                                int heightBox, int durationBox,
                                int nmeasureBox, QList<MolStruct> mols)
{
    // General settings
    paramSimu->setLength(lengthBox);
    paramSimu->setHeight(heightBox);
    paramSimu->setWidth(widthBox);
    paramSimu->setIter(durationBox);
    paramSimu->setNmeasure(nmeasureBox);
    paramSimu->setMols(mols);

}

void SimuHandler::launchSimu()
{
    cpuSimu= new CPU();
    cpuSimu->init(paramSimu);
    cpuSimu->setStepNb(iterByStep);

    fr = cpuSimu->getEnv();

    // Setup visualisation
    if(isVisu)
    {
        visu = new VisuUI();
        VisuCaption vcapt = cpuSimu->get_caption();
        visu->setScene(fr,
                       paramSimu->getLength(),
                       paramSimu->getHeight(),
                       paramSimu->getWidth(),
                       vcapt.fc_dims,
                       vcapt.dfc_dims);
        visu->setCaption(vcapt);
        
        visu->show();
    }

    connect(cpuSimu, SIGNAL(stepDone()), this, SLOT(updateVisu()));
    connect(cpuSimu, SIGNAL(finished()), this, SLOT(simuDone()));
    connect(cpuSimu, SIGNAL(progress(int)), visu, SLOT(setProgress(int)));

    visu->togglePlayButton();
    connect(visu, SIGNAL(resumeSimu()), this, SLOT(resumeSimu()));
    connect(visu, SIGNAL(pauseSimu()), this, SLOT(pauseSimu()));

    connect(visu, SIGNAL(stopSimu()), this, SLOT(stopSimu()));
    connect(visu, SIGNAL(changeSpeedSimu(int)),
            cpuSimu, SLOT(setSpeedSimu(int)));
    
    // Compute simulation
    visu->setTitle(tr("Simulation is running"));
    cpuSimu->start();
}

void SimuHandler::updateVisu()
{
    visu->update();
}

void SimuHandler::simuDone()
{
    // Get Results
    Results *resu = new Results(cpuSimu->get_results());
    
    visu->setTitle(tr("Simulation is done"));
    visu->simuIsDone();
    emit simuIsDone(resu);
}

void SimuHandler::resumeSimu()
{
    visu->setTitle(tr("Simulation is running"));
    cpuSimu->resumeSimu();
}

void SimuHandler::pauseSimu()
{
    visu->setTitle(tr("Simulation is paused"));
    cpuSimu->pauseSimu();
}

void SimuHandler::stopSimu()
{
    cpuSimu->setStopFlag(true);
}
