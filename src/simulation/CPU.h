/*
 * CPU.h
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

#ifndef CPU_HEADER
#define CPU_HEADER

#include "compute.h"
#include "agent.h"
#include <vector>


class CPU : public Compute
{
    Q_OBJECT

    private:
    int dfc_length;
    int dfc_height;
    int dfc_width;
    int fc_length;
    int fc_height;
    int fc_width;
    int nbMolecule_agent;
    int nbRna;
    Molecule_agent * molecules;
    std::vector <Molecule_agent>  rnas;
    Transcriptor * transcriptors;
    void unFlag( int frame);
    void setFlag(MolStruct colonie, int frame);
    void setFlag(Rna_struct colonie, int frame);
    void initCompartments();
    void placeMoleculeAgents();
    void placeTranscriptorAgents();
    int coords2index(int x, int y, int z); 
    template <class T> void shuffleArray(T* array, int array_length);
    void transcriptor_cycle(int indice);
    void protein_cycle(int indice);
    void rna_cycle(int indice,std::vector <int> &removedRnas);
    void look_around(Position * neighbors, Position current);
    bool look_limit(Position current);
    void shuffleArray(std::vector<Molecule_agent> &array, int array_length);
    void fillResults(int indice);
    int out_rna;
    virtual void init_results();
    virtual void step(int nbIterations);  

public:
    CPU();
    virtual void init(ParamAccess * parameters); 
    virtual VisuCaption get_caption();
};

#endif
