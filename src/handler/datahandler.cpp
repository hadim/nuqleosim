/*
 * datahandler.cpp
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

#include "datahandler.h"

DataHandler::DataHandler(QString fdatabase, QString fschema)
{
    // Init model
    molModel = new QList<QTreeWidgetItem *>;
    expModel = new QList<QTreeWidgetItem *>;

    // Init database
    db = new XmlAccess(fdatabase, fschema);

    // Load data
    loadData();

}

QList<QTreeWidgetItem *> DataHandler::getMolModel()
{
    return *molModel;
}

QList<QTreeWidgetItem *> DataHandler::getExpModel()
{
    return *expModel;
}

bool DataHandler::loadData()
{
    int i;

    // Set molecules data to model
    i = 0;
    foreach(Molecule mol, db->getMolecules())
    {
        QStringList list;
        list << mol["id"].toString() << mol["name"].toString();
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0,
                                                    list);
        molModel->append(item);
        molIndex[mol["id"].toInt()] = i;
        i++;
    }

    // Set experiments data to model
    i = 0;
    foreach(Experiment exp, db->getExperiments())
    {
        QStringList list;
        list << exp["id"].toString() << exp["name"].toString();
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0,
                                                    list);
        expModel->append(item);
        expIndex[exp["id"].toInt()] = i;
        i++;
    }

    return true;
}

MoleculeUI* DataHandler::getMolWidget(int index)
{
    Molecule mol;
    if(db->getMolecule(index, mol) == true)
    {
        currentMol = new MoleculeUI(mol);
        connect(currentMol, SIGNAL(molChanged(Molecule&)),
                this, SLOT(molChanged(Molecule&)));
        connect(currentMol, SIGNAL(molRemove(Molecule&)),
                this, SLOT(molRemove(Molecule&)));
        return currentMol;
    }
    else{
        qWarning() << "No molecule with id " << index;
        return NULL;
    }
}

ExperimentUI* DataHandler::getExpWidget(int index)
{
    Experiment exp;
    if(db->getExperiment(index, exp) == true)
    {
        currentExp = new ExperimentUI(exp);
        connect(currentExp, SIGNAL(expChanged(Experiment&)),
                this, SLOT(expChanged(Experiment&)));
        connect(currentExp, SIGNAL(expRemove(Experiment&)),
                this, SLOT(expRemove(Experiment&)));
        return currentExp;
    }
    else{
        qWarning() << "No experiment with id " << index;
        return NULL;
    }
}

void DataHandler::molChanged(Molecule &mol)
{
    db->modifMolecule(mol);

    int index = molIndex[mol["id"].toInt()];
    molModel->at(index)->setText(1, mol["name"].toString());
    
    db->save();
}

void DataHandler::expChanged(Experiment &exp)
{
    db->modifExperiment(exp);

    int index = expIndex[exp["id"].toInt()];
    expModel->at(index)->setText(1, exp["name"].toString());
    
    db->save();
}

void DataHandler::molRemove(Molecule &mol)
{
    int index = molIndex[mol["id"].toInt()];

    emit signal_molRemove(index);

    db->removeMolecule(mol);
    molModel->removeAt(index);
    molIndex.remove(mol["id"].toInt());
    
    db->save();
}

void DataHandler::expRemove(Experiment &exp)
{
    int index = expIndex[exp["id"].toInt()];

    emit signal_expRemove(index);

    db->removeExperiment(exp);
    expModel->removeAt(index);
    expIndex.remove(exp["id"].toInt());
    
    db->save();
}

QTreeWidgetItem* DataHandler::molAdd()
{
    Molecule mol;
    int id = db->addMolecule(mol);
    mol["id"] = id;

    QStringList list;
    list << mol["id"].toString() << mol["name"].toString();
    QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0,
                                                list);
    molModel->append(item);
    molIndex[mol["id"].toInt()] = molModel->indexOf(item);

    return item;
}

QTreeWidgetItem* DataHandler::expAdd()
{
    Experiment exp;
    int id = db->addExperiment(exp);
    exp["id"] = id;

    QStringList list;
    list << exp["id"].toString() << exp["name"].toString();
    QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0,
                                                list);
    expModel->append(item);
    expIndex[exp["id"].toInt()] = expModel->indexOf(item);

    return item;
}
