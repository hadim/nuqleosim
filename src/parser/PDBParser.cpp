/*
 * PDBParser.cpp
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

#include <QtDebug>
#include <QtXmlPatterns>

#include "PDBParser.h"

PDBParser::PDBParser()
{
    extension="pdb";
    residueConverter.insert("ALA" , 'A'); 
    residueConverter.insert( "ARG" , 'R');
    residueConverter.insert( "ASN" , 'N'); 
    residueConverter.insert( "ASP" , 'D');
    residueConverter.insert( "CYS" , 'C');
    residueConverter.insert( "GLU" , 'E');
    residueConverter.insert( "GLN" , 'Q');
    residueConverter.insert( "GLY" , 'G');
    residueConverter.insert( "HIS" , 'H'); 
    residueConverter.insert( "ILE" , 'I');
    residueConverter.insert( "LEU" , 'L');
    residueConverter.insert( "LYS" , 'K'); 
    residueConverter.insert("MET" , 'M'); 
    residueConverter.insert( "PHE" , 'F'); 
    residueConverter.insert( "PRO" , 'P');
    residueConverter.insert( "PYL" , 'O');
    residueConverter.insert( "SEC" , 'U'); 
    residueConverter.insert( "SER" , 'S'); 
    residueConverter.insert( "THR" , 'T'); 
    residueConverter.insert(  "TRP" , 'W'); 
    residueConverter.insert( "TYR" , 'Y'); 
    residueConverter.insert("VAL" , 'V' );
    residueConverter.insert("UNK" , '?' );
    residueConverter.insert( " DA" , 'A') ; 
    residueConverter.insert( " DT" , 'T'); 
    residueConverter.insert( " DC" , 'C' ); 
    residueConverter.insert(  " DG" , 'G');
    residueConverter.insert(  "  G" , 'G');
    residueConverter.insert(  "  A" , 'A');
    residueConverter.insert(  "  U" , 'U');
    residueConverter.insert(  "  C" , 'C');
}

QList< Molecule > PDBParser::getMolecule(QString fileName)
{
    this->clearData();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        //qDebug() << "File :"<<fileName<< "can't be opened"<<endl;
    }
    else
    {
        //qDebug() << "Opening :"<< fileName<<endl;
        parseFile(&file);
        file.close();
    }
    return this->data;
}

QList< Molecule > PDBParser::getMoleculeFromPath(QString path)
{
    this->clearData();

    QList< QString > flist = getFileList(path);
    qDebug() << "filelist : " << flist<< endl;
    QString fileName;
    foreach(fileName, flist)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "File :"<<fileName<< "can't be opened"<<endl;
        }
        else
        {
            qDebug() << "Opening :"<< fileName<<endl;
            parseFile(&file);
            file.close();
        }
    }
    return this->data;
}

int PDBParser::parseFile(QFile * file)
{
    QRegExp nameRegExp( "(COMPND)\\s*\\d*\\s*(MOLECULE:\\s)\\s*(.*)" );
    QRegExp sequenceRegExp( "(SEQRES)\\s+\\d+\\s+\\D+\\s+\\d+\\s{2}(.*)" );
    QString an_alphabet="  A  T  G  U  C DA DC DG DT";
    Molecule *map= new Molecule;
    this->initKeys(map);
    bool protein=false;
    bool arn=false;

    QTextStream in(file);
    while (!in.atEnd()) {
        QString line = in.readLine();
       
        if (nameRegExp.indexIn(line)!=-1)
        {
            QString name =nameRegExp.cap(3);
            name=cleanString(name);
            (*map)["name"]=name;
        }
        else if (sequenceRegExp.indexIn(line)!=-1)
        {
            QString sequencePart =cleanString(sequenceRegExp.cap(2));
            QStringList resList=sequencePart.split(" ");
            QString res;
            foreach ( res, resList)
            {
                (*map)["sequence_length"]=(*map)["sequence_length"].toInt()+1;
                if (res == "  U")
                    arn = true;
                if (!an_alphabet.contains(res, Qt::CaseInsensitive))
                    protein = true;
                QChar c = residueConverter[res];
                (*map)["sequence"] = (*map)["sequence"].toString() + c;
            }
        }
    }	   
    if (protein)(*map)["type"]="protein";
    else
    {
        if (arn)(*map)["type"]="arn";
        else (*map)["type"]="adn";
    }
    (*map)["pdb_id"] = getPDBid(file->fileName());

    appendMap(map);

    return 0;
}

QString PDBParser::getPDBid(QString fname)
{
    QStringList fsplit=fname.split("/");
    return fsplit[fsplit.size()-1].split(".")[0];
}

PDBParser::~PDBParser()
{

}





