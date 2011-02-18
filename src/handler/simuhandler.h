/*
 * simuhandler.h
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

#ifndef HEADER_SIMUHANDLER
#define HEADER_SIMUHANDLER

#include <QtGui>

#include "../datamodel/molecule.h"
#include "../datamodel/experiment.h"
#include "../datamodel/image.h"

#include "../paramaccess.h"
#include "../datamodel/mol_struct.h"
#include "../datamodel/resu_struct.h"
#include "../simulation/CPU.h"

#include "../utils/definebug.h"

#include "../visu/visuui.h"
#include "../results/results.h"

class SimuHandler : public QObject
{
    Q_OBJECT

public:
    SimuHandler();

    void setParameters(int lengthBox, int widthBox,
                       int heightBox, int durationBox,
                       int nmeasureBox, QList<MolStruct> mols);
    void launchSimu();

private:
    ParamAccess *paramSimu;
    CPU * cpuSimu;
    int iterByStep;

    UnitFrame* fr;
    int size;

    bool isVisu;
    VisuUI* visu;

private slots:
    void updateVisu();
    void simuDone();

    void resumeSimu();
    void pauseSimu();
    void stopSimu();

signals:
    void simuIsDone(Results *resu);
};


#endif
