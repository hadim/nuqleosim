/*
 * datahandler.h
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

#ifndef HEADER_DATAHANDLER
#define HEADER_DATAHANDLER

#include <QtGui>

#include "../dbaccess/xmlaccess.h"
#include "../datamodel/molecule.h"
#include "../datamodel/experiment.h"
#include "../datamodel/image.h"

#include "../ui/moleculeui.h"
#include "../ui/experimentui.h"

class DataHandler : public QObject
{
    Q_OBJECT

public:
    DataHandler(QString fdatabase, QString fschema);

    QList<QTreeWidgetItem *> getMolModel();
    QList<QTreeWidgetItem *> getExpModel();

    MoleculeUI* getMolWidget(int index);
    ExperimentUI* getExpWidget(int index);

    QTreeWidgetItem* molAdd();
    QTreeWidgetItem* expAdd();

private:
    bool loadData();
    MoleculeUI *currentMol;
    ExperimentUI *currentExp;

    XmlAccess *db;
    QList<QTreeWidgetItem *>* molModel;
    QList<QTreeWidgetItem *>* expModel;

    QMap <int, int> molIndex;
    QMap <int, int> expIndex;

private slots:
    void molChanged(Molecule &mol);
    void expChanged(Experiment &exp);

    void molRemove(Molecule &mol);
    void expRemove(Experiment &exp);

signals:
    void signal_molRemove(int index);
    void signal_expRemove(int index);
    
};


#endif
