/*
 * BioParser.cpp
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

#include "BioParser.h"

BioParser::BioParser()
{

}

BioParser::~BioParser()
{

}

void BioParser::clearData()
{
    this->data.clear();
}

void BioParser::initKeys(Molecule * map)
{
    (*map)["id"]= 0;
    (*map)["name"]= "";
    (*map)["comment"]= "";
    (*map)["element_type"]= "molecule";
    (*map)["path"]= "";
    (*map)["date_catch"]= "";
    (*map)["type"]= "";
    (*map)["sequence_length"]= 0;
    (*map)["sequence"]= "";
    (*map)["default_concentration"]= 0;
  
}

void BioParser::appendMap(Molecule * map)
{
    this->data.append(*map);
}


void BioParser::dataDisplay()
{
    Molecule  map;
    foreach(map, this->data)
    {
      
        qDebug()<<map<<endl;
	}
}

QString BioParser::cleanString(QString str)
{
    bool nasty=true;
    while(nasty)
    {
        QChar  lastChar ;
        lastChar=str[str.size()-1];
        if (lastChar=='\n' || lastChar=='\t' ||
            lastChar==' ' || lastChar==';')
            str.chop(1);
        else
            nasty=false;
    }
    return str;
}

QList< QString > BioParser::getFileList(QString path)
{
    //works only with complete dir path
    QList< QString > flist;
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString fname=it.next();
        if (fname.split(".")[1]==this->extension)
            flist.append(fname);

    }

    return flist;
}
