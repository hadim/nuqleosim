/*
 * BioParser.h
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

#ifndef BIOPARSER_HEADER
#define BIOPARSER_HEADER

#include <QtCore>
#include <QList>

#include "../datamodel/molecule.h"

class BioParser: public QObject
{

    Q_OBJECT

    public:
    BioParser();
    virtual ~BioParser();

    QList< Molecule > getData();
    virtual QList< Molecule > getMolecule(QString) = 0;
    virtual QList< Molecule > getMoleculeFromPath(QString) = 0;

protected:
    QList< Molecule > data;
    QString extension;

    virtual int parseFile(QFile *) = 0;  
    QList< QString > getFileList(QString);

    QString cleanString(QString);
    void initKeys(Molecule *);
    void appendMap(Molecule *);
    void clearData();
    void dataDisplay();
};

#endif

