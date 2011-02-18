/*
 * CPU.cpp
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

#include "CPU.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define NB_TRANSCRIPTORS 2
#define DFC_SIZE 0.5
#define FC_SIZE 0.25
#define RNA1_COLOR {255,255,0}
#define RNA2_COLOR {255,100,0}
#define RNA3_COLOR {255,0,0}
#define RNA_GENERATION_PROBA 0.9
#define MATURE_PROBA 0.2
#define LEAVE_PROBA 0.5
#define BLACK {0,0,0}

CPU::CPU()
{
    speedSimu = 500;
}


int CPU::coords2index(int x, int y, int z)
{
  int tmp= (length*height *z)+(length*y)+x;
  return tmp;
}

void CPU::setFlag(MolStruct colonie, int frame)
{
  environment[frame].color=colonie.color;
  environment[frame].flag=colonie.flag;
}

void CPU::setFlag(Rna_struct colonie, int frame)
{
  environment[frame].color=colonie.color;
  environment[frame].flag=colonie.flag;
}

void CPU::unFlag( int frame)
{
  environment[frame].color=BLACK;
  environment[frame].flag=no_flag;
}

void CPU::placeMoleculeAgents()
{
  int cpt_agents=0;
  for(int c=0; c<nbColonies; c++)
    {
      int frame;
      //Fill FC compartment
      for (int i=0; i< colonies[c].FC_number; i++)
        {
	  bool found=false;
	  int x, y, z;
	  do {
	    x= (int)((double)rand() / ((double)RAND_MAX ) * length);
	    y=(int)((double)rand() / ((double)RAND_MAX ) * height);
	    z=(int)((double)rand() / ((double)RAND_MAX ) * width);
	    frame=coords2index( x, y, z);
	    if (environment[frame].compartment==FC_comp &&
		environment[frame].flag==no_flag )found =true;
	  }while(not found);
	  setFlag(colonies[c],frame);
	  Molecule_agent tmpAgent;
	  Position pos;
	  pos.x=x;
	  pos.y=y;
	  pos.z=z;
	  tmpAgent.position=pos;
	  tmpAgent.colony=c;
	  molecules[cpt_agents++]=tmpAgent;      
        }
      //Fill DFC compartment
      for (int i=0; i< colonies[c].DFC_number; i++)
        {
	  bool found=false;
	  int x, y, z;
	  do {
	    x= (int)((double)rand() / ((double)RAND_MAX ) * length);
	    y=(int)((double)rand() / ((double)RAND_MAX ) *height);
	    z=(int)((double)rand() / ((double)RAND_MAX ) * width);      
	    frame=coords2index( x, y, z);     
	    if (environment[frame].compartment==DFC_comp &&
		environment[frame].flag==no_flag )found =true;    
	  }while(not found);	   
	  setFlag(colonies[c],frame);
	  Molecule_agent tmpAgent;
	  Position pos;
	  pos.x=x;
	  pos.y=y;
	  pos.z=z;
	  tmpAgent.position=pos;
	  tmpAgent.colony=c;
	  molecules[cpt_agents++]=tmpAgent;
      
        }
      //Fill GC compartment
      for (int i=0; i< colonies[c].GC_number; i++)
        {
	  bool found=false;
	  int x, y, z;
	  do {
	    x= (int)((double)rand() / ((double)RAND_MAX ) * length);
	    y=(int)((double)rand() / ((double)RAND_MAX ) *height);
	    z=(int)((double)rand() / ((double)RAND_MAX ) * width);
	    frame=coords2index( x, y, z);
	    if (environment[frame].compartment==GC_comp &&
		environment[frame].flag==no_flag )found =true;
	  } while(not found);
	  setFlag(colonies[c],frame);
	  Molecule_agent tmpAgent;
	  Position pos;
	  pos.x=x;
	  pos.y=y;
	  pos.z=z;
	  tmpAgent.position=pos;
	  tmpAgent.colony=c;
	  molecules[cpt_agents++]=tmpAgent;
        } 
    }
}

void CPU::placeTranscriptorAgents()
{
  for(int c=0; c<NB_TRANSCRIPTORS; c++)
    {
      int frame;
      bool found=false;
      int x, y, z;
      do {
	x= (int)((double)rand() / ((double)RAND_MAX ) * length);
	y=(int)((double)rand() / ((double)RAND_MAX ) *height);
	z=(int)((double)rand() / ((double)RAND_MAX ) * width);
	frame=coords2index( x, y, z);
	if (environment[frame].compartment==FC_comp )found =true;
      }while(not found);
      Transcriptor_agent tmpAgent;
      Position pos;
      pos.x=x;
      pos.y=y;
      pos.z=z;
      tmpAgent.position=pos;
      transcriptors[c]=tmpAgent;
    }
}

void CPU::initCompartments()
{
  for(int z=0; z<width;z++)
    {
      for(int y=0; y<height;y++)
        {
	  for(int x=0; x<length;x++)
            {
	      environment[coords2index(x, y, z)].pos={x,y,z};
	      //test if FC
	      if ((z> (width/2)-(fc_width/2) && z<(width/2)+(fc_width/2)) 
		  && (y> (height/2)-(fc_height/2) && y<(height/2)+(fc_height/2))
		  && (x> (length/2)-(fc_length/2) && x<(length/2)+(fc_length/2)))
                {
		  environment[coords2index(x, y, z)].compartment=FC_comp; 
		  unFlag(coords2index(x, y, z));	  
                }
	      else
		//test if DFC
		if ((z> (width/2)-(dfc_width/2) && z<(width/2)+(dfc_width/2)) 
		    && (y> (height/2)-(dfc_height/2) && y<(height/2)+(dfc_height/2))
		    && (x> (length/2)-(dfc_length/2) && x<(length/2)+(dfc_length/2)))
		  {
		    environment[coords2index(x, y, z)].compartment=DFC_comp; 
		    unFlag(coords2index(x, y, z));
		  }
		else{
		  environment[coords2index(x, y, z)].compartment=GC_comp; 
		  unFlag(coords2index(x, y, z));
		}         
            }
        }
    }
}



void CPU::init_results()
{
 
  results->stepSize=(int)(iterTot/(results->nbPlots));
  if (results->stepSize<1) results->stepSize=1;
  results->fc_rna1= new int[results->nbPlots];
  results->fc_rna2= new int[results->nbPlots];
  results->fc_rna3= new int[results->nbPlots];
  results->dfc_rna1= new int[results->nbPlots];
  results->dfc_rna2= new int[results->nbPlots];
  results->dfc_rna3= new int[results->nbPlots];
  results->gc_rna1= new int[results->nbPlots];
  results->gc_rna2= new int[results->nbPlots];
  results->gc_rna3= new int[results->nbPlots];
  results->out_rna= new int[results->nbPlots];
  for (int i =0; i<results->nbPlots;i++)
    {
      results->fc_rna1[i]=0;
      results->fc_rna2[i]=0;
      results->fc_rna3[i]=0;
      results->dfc_rna1[i]=0;
      results->dfc_rna2[i]= 0;
      results->dfc_rna3[i]= 0;
      results->gc_rna1[i]= 0;
      results->gc_rna2[i]= 0;
      results->gc_rna3[i]= 0;
      results->out_rna[i]= 0;
    }
}




void CPU::init(ParamAccess * parameters)
{
  cpt_iter=0;
  srand(time(NULL));
  //getting parameters 
  stepNb=10;
  length=parameters->getLength();
  height=parameters->getHeight();
  width=parameters->getWidth();
  iterTot = parameters->getIter();
  dfc_length=(int)(length*DFC_SIZE);
  dfc_height=(int)(height * DFC_SIZE);
  dfc_width= (int)(width *DFC_SIZE);
  fc_length=(int)(length * FC_SIZE);
  fc_height= (int)(height *FC_SIZE);
  fc_width= (int)(width *FC_SIZE);
  colonies = parameters->getMols();
  nbColonies = colonies.size();
  nbColoniesRna = 3;
  nbRna=0;
  out_rna=0;
  //computing the number of Protein 
  nbMolecule_agent=0;
  for(int i=0; i<nbColonies; i++)
    {
      colonies[i].flag=protein_flag;
      colonies[i].DFC_number=(int)((colonies[i].DFC_pourcentage/100.0) * dfc_width*dfc_height*dfc_length);
      colonies[i].FC_number=(int)((colonies[i].FC_pourcentage/100.0)*fc_width*fc_height*fc_length);
      colonies[i].GC_number=(int)((colonies[i].GC_pourcentage/100.0)*width*height*length);
      nbMolecule_agent+=colonies[i].DFC_number+ colonies[i].FC_number +colonies[i].GC_number;
    }
  //creation of the proteins colors
  int colorStep=255/nbColonies;
  if (colorStep<1) colorStep=1;
  int green=0;
  int blue=255;
  for (int i=0; i<nbColonies; i++)
    {
      colonies[i].color={0,green,blue};
      green=(green+colorStep);
      if (green>255) green=255;
      blue=(blue-colorStep);
      if (blue<0) blue=1;
    }
  //  setting of the rna colonies
  coloniesRna = new Rna_struct[nbColoniesRna];
  coloniesRna[0]={'R',true,true,false,false,rna_flag,RNA1_COLOR};
  coloniesRna[1]={'R',false,true,true,false,rna_flag,RNA2_COLOR};
  coloniesRna[2]={'R',false,false,true,true,rna_flag,RNA3_COLOR};
  // memory allocation for agents arrays
  molecules= new Molecule_agent[nbMolecule_agent];
  transcriptors = new Transcriptor[NB_TRANSCRIPTORS];
  //creation of the environment
  environment= new UnitFrame[length*height*width];
  initCompartments();
  //initialisation of proteins
  placeMoleculeAgents();
  //initialisation of transcriptors
  placeTranscriptorAgents();
  //initialisation of the Results
  results= new Resu_struct(); 
  results->nbPlots=parameters->getNmeasure()+1;
  init_results();
}

template <class T> void CPU::shuffleArray(T* array, int array_length)
{
  for (int i=0; i<array_length; i++) {
    int r =rand()% array_length; ; // Random remaining position.
    T temp = array[i]; 
    array[i] = array[r];
    array[r] = temp;
  }
}


void CPU::shuffleArray(std::vector<Molecule_agent> &array, int array_length)
{
  for (int i=0; i<array_length; i++) {
    int r =rand()% array_length; ; // Random remaining position.
    Molecule_agent temp = array[i]; 
    array[i] = array[r];
    array[r] = temp;
  }
}



bool CPU::look_limit(Position current)
{
  int X=length;
  int Y=height;
  int Z=width;
  if ((current.x==0)
      or (current.x==X-1)
      or (current.y==0)
      or (current.y==Y-1)
      or (current.z==0)
      or (current.z==Z-1))
    return true;
  else return false;
}

void CPU::look_around( Position * neighbors, Position current)
{
     
  int X=length;
  int Y=height;
  int Z=width;
  int bordX=0;
  int bordY=0;
  int bordZ=0;

  // Look if current frame is near a border X, Y or Z
  if (current.x==0)
    bordX=1;
  else if (current.x==X-1)
    bordX=2;
  if (current.y==0)
    bordY=1;
  else if (current.y==Y-1)
    bordY=2;
  if (current.z==0)
    bordZ=1;
  else if (current.z==Z-1)
    bordZ=2;

  // Add neighbor frame to current frame in frames array

  int cpt =0;

  int x, y, z;
  for(int dx=-1;dx<2;dx++)
    {
      if(bordX==1 && dx==-1)
        {
	  x=X-1;
        }
      else if(bordX==2 && dx==1)
        {
	  x=0;
        }
      else x=current.x+dx;
      for(int dy=-1;dy<2;dy++)
        {
	  if(bordY==1 && dy==-1)
            {
	      y=Y-1;
            }
	  else if(bordY==2 && dy==1)
            {
	      y=0;
            }
	  else y=current.y+dy;
	  for(int dz=-1;dz<2;dz++)
            {
	      if(bordZ==1 && dz==-1)
                {
		  z=Z-1;
                }
	      else if(bordZ==2 && dz==1)
                {
		  z=0;
                }
	      else z=current.z+dz;
	      Position neighbor={x,y,z};
	      neighbors[cpt]=neighbor;
	      cpt++;
	      //std::cout<<neighbor.x<<std::endl;
            }
        }
    }
}

void CPU::protein_cycle(int indice)
{

 

  Molecule_agent current=molecules[indice];
  Position * neighbors =new Position[27];
  look_around(neighbors, current.position);

  //search free frames in the accessible compartments
  std::vector <Position> freeFrames;
  for (int i =0; i<27; i++)
    {
      UnitFrame frame=environment[coords2index(neighbors[i].x,neighbors[i].y,neighbors[i].z)];
      MolStruct col=colonies[current.colony];
      if(frame.flag==no_flag
	 && ((frame.compartment==FC_comp and col.FC_access) 
	     || (frame.compartment==DFC_comp and col.DFC_access) 
	     || (frame.compartment==GC_comp and col.GC_access)))
	freeFrames.push_back(neighbors[i]);
    }
  //then choose a random frame  and move(if possible)


  if (freeFrames.size()!=0)
    {
      float move_score= (float)( (double)rand() / ((double)RAND_MAX + 1));
      if (move_score < colonies[current.colony].mov_proba)
        {
	  int r= rand()% freeFrames.size();
	  molecules[indice].position=freeFrames[r];
	  //puts a flag on its new frame
	  setFlag(colonies[current.colony], coords2index(freeFrames[r].x,freeFrames[r].y,freeFrames[r].z));
	  //unflag the former frame 
	  unFlag(coords2index(current.position.x,current.position.y,current.position.z));
        }
    }
    
  delete [] neighbors;
}

void CPU::rna_cycle(int indice, std::vector<int> &removedRnas)
{
  Molecule_agent current=rnas[indice];
  Position * neighbors =new Position[27];
  look_around(neighbors, current.position);
  bool protein_close=false;
  //search a protein in the neighborhood
  for (int i =0; i<27; i++)
    {
      if(environment[coords2index(neighbors[i].x,neighbors[i].y,neighbors[i].z)].flag==protein_flag)
	protein_close=true;
    }
  
  //if there is a protein , not final state, AND  if arn in the good compartment  try to mature
  if ( current.colony<2)
    {
      Compartment comp=environment[coords2index(current.position.x,current.position.y,current.position.z)].compartment;
      float mature_score;
      if( protein_close && rnas[indice].colony==0 && comp==DFC_comp) 
	mature_score =(float)( (double)rand() / ((double)RAND_MAX + 1));
      else if ( protein_close && rnas[indice].colony==1 && comp==GC_comp) 
	mature_score =(float)( (double)rand() / ((double)RAND_MAX + 1));
      else mature_score=1;
      if (mature_score<MATURE_PROBA) rnas[indice].colony++ ;
    }

  //if a limit of GC is close, and rna completely mature, try to leave the nucleolus
  bool out=false;
  if (coloniesRna[current.colony].ext_access)
    {
      bool limit = look_limit(current.position);
      if (limit) 
        {
	  float leave_score;
	  leave_score=(float)( (double)rand() / ((double)RAND_MAX + 1)); 
	  if (leave_score<LEAVE_PROBA) 
            {
	      out=true;
	      removedRnas.push_back(indice);
	      unFlag(coords2index(current.position.x,current.position.y,current.position.z));
            }
        }
    }
  //search  free frames in the accessible compartments
  if (!out)
    {
      std::vector <Position> freeFrames;
      for (int i =0; i<27; i++)
        {
	  UnitFrame frame=environment[coords2index(neighbors[i].x,neighbors[i].y,neighbors[i].z)];
	  Rna_struct col=coloniesRna[current.colony];
	  if(frame.flag==no_flag
	     && ((frame.compartment==FC_comp and col.FC_access) 
		 || (frame.compartment==DFC_comp and col.DFC_access) 
		 || (frame.compartment==GC_comp and col.GC_access)))
	    freeFrames.push_back(neighbors[i]);
        }
      //then choose a random frame  and move(if possible)
      if (freeFrames.size()!=0)
        {
	  int r= rand()% freeFrames.size();
	  rnas[indice].position=freeFrames[r];
	  //puts a flag on its new frame
	  setFlag(coloniesRna[current.colony], coords2index(freeFrames[r].x,freeFrames[r].y,freeFrames[r].z));
	  //unflag the former frame 
	  unFlag(coords2index(current.position.x,current.position.y,current.position.z));
        }
    }
  delete [] neighbors;
}

void CPU::transcriptor_cycle(int indice)
{
  Transcriptor_agent current=transcriptors[indice];
  Position * neighbors =new Position[27];
  look_around(neighbors, current.position);
  //search  free frames to release arn
  std::vector <Position> freeFrames;
  for (int i =0; i<27; i++)
    {
      if(environment[coords2index(neighbors[i].x,neighbors[i].y,neighbors[i].z)].flag==no_flag)
	freeFrames.push_back(neighbors[i]);
    }
  //try to release a new arn if there is a free frame
  if (freeFrames.size()!=0)
    {
      float gen_score=(float)( (double)rand() / ((double)RAND_MAX + 1)); ;
      if (gen_score<RNA_GENERATION_PROBA)
        {
	  int r= rand()% freeFrames.size();
	  Molecule_agent _arn;
	  _arn.position= freeFrames[r];
	  _arn.colony=0;
	  rnas.push_back(_arn);
	  setFlag(coloniesRna[0], coords2index(_arn.position.x,_arn.position.y,_arn.position.z));
	  nbRna++;
        }
    }
  //move in the Fc compartment
  // first look for the neighbor frames in FC
  std::vector <Position> FCFrames;
  for (int i =0; i<27; i++)
    {
      if(environment[coords2index(neighbors[i].x,neighbors[i].y,neighbors[i].z)].compartment==FC_comp)
	FCFrames.push_back(neighbors[i]);
    }
  //then choose a random frame  and move
  if (FCFrames.size()!=0)
    {
      int r= rand()% FCFrames.size();
      transcriptors[indice].position=freeFrames[r];
    }
  delete [] neighbors;
}


void CPU::fillResults(int indice)
{
  for(int i=0; i<nbRna;i++)
    {
      Molecule_agent current=rnas[i];
      Compartment comp=environment[coords2index(current.position.x,current.position.y,current.position.z)].compartment;
      int col=current.colony;
      if (comp==FC_comp)
	{
	  if (col==0)results->fc_rna1[indice]++;
	  if (col==1)results->fc_rna2[indice]++;
	  if (col==2)results->fc_rna3[indice]++;
	}
      if (comp==DFC_comp)
	{	  
	  if (col==0)results->dfc_rna1[indice]++;
	  if (col==1)results->dfc_rna2[indice]++;
	  if (col==2)results->dfc_rna3[indice]++;
	}
      if (comp==GC_comp)
	{
	  if (col==0)results->gc_rna1[indice]++;
	  if (col==1)results->gc_rna2[indice]++;
	  if (col==2)results->gc_rna3[indice]++;
	}
    }
  results->out_rna[indice]=out_rna;
}


void CPU::step(int nbIterations)
{
 
  //Does the number of iterations asked
  for (int iter=0; iter<nbIterations; iter++)
    {
      //Each transcriptor does its cycle
      shuffleArray(transcriptors,NB_TRANSCRIPTORS );

      for( int i =0; i<NB_TRANSCRIPTORS; i++)
        {
	  transcriptor_cycle(i);
        }

      //Each protein does its cycle
      shuffleArray(molecules,nbMolecule_agent);
      for( int i =0; i<nbMolecule_agent; i++)
        {
	  protein_cycle(i);
        }

      //Each arn does its cycle
      shuffleArray(rnas,nbRna );
      std::vector <int>  removedRnas;
      for( int i =0; i<nbRna; i++)
        {
	  rna_cycle(i,removedRnas);
        }
      //Remove the Rnas that left the nuclolus
      for (uint i=0;i<removedRnas.size(); i++)
        { 
	  rnas.erase(rnas.begin()+(removedRnas[i]-i));
	  nbRna--;
	  out_rna++;
        }
      cpt_iter++;
      if ((cpt_iter%(results->stepSize)==0 )
	  && (cpt_iter <(results->stepSize* results->nbPlots)))
	{	  
	  fillResults(cpt_iter/(results->stepSize));
	}
    }

}


VisuCaption CPU::get_caption() 
{
  VisuCaption capt;
  capt.proteins= new ProtCaption[nbColonies];
  capt.rnas= new RnaCaption[nbColoniesRna];

  capt.fc_dims = new int[3];
  capt.dfc_dims = new int[3];
    
  for (int i=0; i<nbColonies; i++)
    {
      capt.proteins[i].name=colonies[i].name;
      capt.proteins[i].color=colonies[i].color;
    }
    
  for (int i=0; i<nbColoniesRna; i++)
    {
      capt.rnas[i].name=i;
      capt.rnas[i].color=coloniesRna[i].color;
    }

  capt.nproteins = nbColonies;
  capt.nrnas = nbColoniesRna;

  capt.fc_dims[0]=fc_length;
  capt.fc_dims[1]=fc_height;
  capt.fc_dims[2]=fc_width;
  capt.dfc_dims[0]= dfc_length;
  capt.dfc_dims[1]=dfc_height;
  capt.dfc_dims[2]=dfc_width;
    
  return capt;
}
