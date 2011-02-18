/*
 * xmlaccess.h
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

#ifndef XMLACCESS_H
#define XMLACCESS_H

#include <QtCore>
#include <QtXmlPatterns>
#include <QtXml>

#include "dbaccess.h"

#include "../datamodel/molecule.h"
#include "../datamodel/experiment.h"
#include "../datamodel/image.h"

class XmlAccess : public DBAccess
{

    Q_OBJECT

public:
    XmlAccess(QString fname, QString fschema);
    ~XmlAccess();

    bool validate();
    QStringList xquery(QString request);
    
    // Get method
    QList <Molecule> getMolecules();
    QList <Experiment> getExperiments();

    bool getMolecule(int id, Molecule &gmol);
    bool getExperiment(int id, Experiment &gexp);
    
    // Add method
    int addMolecule(Molecule mol);
    int addExperiment(Experiment exp);

    // remove method
    bool removeMolecule(Molecule mol);
    bool removeExperiment(Experiment exp);

    // modify method
    bool modifMolecule(Molecule mol);
    bool modifExperiment(Experiment exp);

    bool save();

protected:
    void setMaxId();
    QDir path2db;

    QDomDocument dbdoc;
    QDomElement root;

    QFile fdb;
    QXmlSchema schema;
    QXmlQuery query;
    bool valid;

    int molMaxId;
    int imgMaxId;
    int expMaxId;
};

#endif
