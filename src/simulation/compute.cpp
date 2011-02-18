/*
 * compute.cpp
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

#include "compute.h"

#include <vector>
void Compute::setStepNb(int _stepNb)
{
  stepNb=_stepNb;
}


UnitFrame* Compute::getEnv()
{
  return environment;
}


Resu_struct * Compute::get_results()
{
  return results;
}



void Compute::run()
{
  stopFlag = false;
  int i;
  int global_iter = ( iterTot / stepNb );
  int p = 0;
  int tmp_p = 0;
  doSimu = true;

  i = 0;
  while(i < global_iter && !stopFlag)
    {
      if(doSimu)
        {
	  step(stepNb);
	  emit stepDone();
        
            tmp_p = 100 * i * stepNb / iterTot;
            if(p != tmp_p)
                emit progress(p);
            p = tmp_p;
            i++;
            msleep(speedSimu);
        }
        else
        {
            msleep(200);
        }
    }
    emit progress(100);
}

void Compute::pauseSimu()
{
  doSimu = false;
}

void Compute::resumeSimu()
{
  doSimu = true;
}

void Compute::setStopFlag(bool b)
{
  stopFlag = true;
}

void Compute::setSpeedSimu(int s)
{
    speedSimu = 1000 - s;
}
