/*
 * simuui.cpp
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

#include "simuui.h"

#include "ui_helpui.h"

SimuUI::SimuUI(QList<QTreeWidgetItem *> _molModel,
               QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    simuHand = new SimuHandler();

    // Init help window
    helpWidget = new QDialog();
    Ui::HelpWidget ui;
    ui.setupUi(helpWidget);
    
    // Set molecules model
    dataMolModel = _molModel;

    // Set default mol
    default_mol.id = -1;
    default_mol.name = "";
    default_mol.DFC_pourcentage = 0;
    default_mol.FC_pourcentage = 0;
    default_mol.GC_pourcentage = 0;
    default_mol.DFC_access = true;
    default_mol.FC_access = false;
    default_mol.GC_access = true;
    default_mol.mov_proba = 1;

    // Set default value
    lengthBox->setValue(20);
    heightBox->setValue(20);
    widthBox->setValue(20);
    durationBox->setValue(500);
    
    // Update accessible state
    on_fcAccessBox_stateChanged(fcAccessBox->checkState());
    on_dfcAccessBox_stateChanged(dfcAccessBox->checkState());
    on_gcAccessBox_stateChanged(gcAccessBox->checkState());

}

void SimuUI::loadMolList()
{
    foreach(QTreeWidgetItem * item, dataMolModel)
    {
        QStringList list;
        list << item->text(0) << item->text(1);
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0,
                                                    list);
     
        molModel.append(item);
    }

    molsWidget->addTopLevelItems(molModel);

}

void SimuUI::on_launchButton_clicked()
{
    // Compute if there is not too much molecules in the cube
    int max = lengthBox->value() * widthBox->value() * heightBox->value();
    int nmols = 0;
    foreach(MolStruct mol, mols)
    {
        nmols += mol.DFC_pourcentage * max / 100;
        nmols += mol.FC_pourcentage * max / 100;
        nmols += mol.GC_pourcentage * max / 100;
    }

    if(nmols > 0.8*max)
    {
        QMessageBox::warning(this,
                             tr("Too much molecules"),
                             tr("Sorry but there is too much molecules "
                                "compared to the size of cellular space. "
                                "Please, change molecules concentrations."),
                             QMessageBox::Close,
                             QMessageBox::Close);
    }
    else if(mols.length() == 0)
    {
        QMessageBox::warning(this,
                             tr("No molecule selected"),
                             tr("Please, select at least one molecule"),
                             QMessageBox::Close,
                             QMessageBox::Close);
    }
    else if(nmeasureBox->value() > durationBox->value())
    {
        QMessageBox::warning(this,
                             tr("Wrong number of measures"),
                             tr("Number of measure need to be lower than duration."),
                             QMessageBox::Close,
                             QMessageBox::Close);
    }
    else
    {
        simuHand->setParameters(lengthBox->value(), widthBox->value(),
                                heightBox->value(), durationBox->value(),
                                nmeasureBox->value(), mols);

        connect(simuHand, SIGNAL(simuIsDone(Results*)),
                this, SLOT(simuIsDone(Results*)));
        setLaunchButtonEnabled(false);
        simuHand->launchSimu();
    }
}

void SimuUI::setLaunchButtonEnabled(bool b)
{
    launchButton->setEnabled(b);
}

void SimuUI::on_helpButton_clicked()
{
    helpWidget->exec();
}

void SimuUI::on_molsWidget_clicked()
{
    molEditBox->setEnabled(true);

    QTreeWidgetItem * current = molsWidget->currentItem();
    
    int id = current->text(0).toInt();
    QString name = current->text(1);

    MolStruct mol;
    bool checked = true;
    int id_loc = molInList(name);

    if(id_loc == -1)
    {
        mol = default_mol;
        mol.id = id;
        mol.name = name.toStdString();
        checked = false;
        fillMolWidget(mol, checked);
    }
    else
        fillMolWidget(mols[id_loc], checked);
    
}

void SimuUI::fillMolWidget(MolStruct mol, bool checked)
{
    gcAccessBox->setEnabled(true);

    selectMol->setChecked(checked);

    nameLabel->setText(QString::fromStdString(mol.name));
    
    fcConcBox->setValue(mol.FC_pourcentage);
    dfcConcBox->setValue(mol.DFC_pourcentage);
    gcConcBox->setValue(mol.GC_pourcentage);

    movProbaBox->setValue(mol.mov_proba);

    fcAccessBox->setChecked(mol.FC_access);
    dfcAccessBox->setChecked(mol.DFC_access);
    gcAccessBox->setChecked(mol.GC_access);
}

void SimuUI::on_selectMol_clicked()
{
    QTreeWidgetItem * current = molsWidget->currentItem();

    int id = current->text(0).toInt();
    QString name = current->text(1);

    bool checked;
    MolStruct mol;

    if(selectMol->isChecked())
    {
        // Change background
        current->setBackground(0, Qt::red);
        current->setBackground(1, Qt::red);

        // Create mol structure
        mol.id = id;
        mol.name = name.toStdString();

        mol.FC_pourcentage = fcConcBox->value();
        mol.DFC_pourcentage = dfcConcBox->value();
        mol.GC_pourcentage = gcConcBox->value();

        mol.FC_access = fcAccessBox->isChecked();
        mol.DFC_access = dfcAccessBox->isChecked();
        mol.GC_access = gcAccessBox->isChecked();

        mol.mov_proba = movProbaBox->value();

        checked = true;

        mols.append(mol);
    }
    else
    {
        // Change background
        current->setBackground(0, Qt::white);
        current->setBackground(1, Qt::white);
        
        // Remove it
        removeMolInList(name);
    }
}

void SimuUI::on_nameLabel_clicked()
{
    if(selectMol->isChecked())
        selectMol->setChecked(false);
    else
        selectMol->setChecked(true);
    on_selectMol_clicked();
}

int SimuUI::molInList(QString name)
{
    int i = 0;
    foreach(MolStruct mol, mols)
    {
        if(name == QString::fromStdString(mol.name))
        {
            return i;
        }
        i++;
    }

    return -1;
}

bool SimuUI::removeMolInList(QString name)
{
    int i = 0;
    foreach(MolStruct mol, mols)
    {
        if(name == QString::fromStdString(mol.name))
        {
            mols.removeAt(i);
            return true;
        }
        i++;
    }

    return false;
}

void SimuUI::on_fcConcBox_valueChanged(double c)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);

        mols[id].FC_pourcentage = c;
    }
}

void SimuUI::on_dfcConcBox_valueChanged(double c)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);
        
        mols[id].DFC_pourcentage = c;
    }
}

void SimuUI::on_gcConcBox_valueChanged(double c)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);
        
        mols[id].GC_pourcentage = c;
    }
}

void SimuUI::on_fcAccessBox_stateChanged(int state)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);

        if(state == Qt::Unchecked)
        {
            mols[id].FC_access = false;
            mols[id].FC_pourcentage = 0;
        }
        else
        {
            mols[id].FC_access = true;
        }
    }

    if(state == Qt::Unchecked)
        fcConcBox->setEnabled(false);
    else
        fcConcBox->setEnabled(true);

}

void SimuUI::on_dfcAccessBox_stateChanged(int state)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);
        
        if(state == Qt::Unchecked)
        {
            mols[id].DFC_access = false;
            mols[id].DFC_pourcentage = 0;
        }
            
        else
            mols[id].DFC_access = true;

    }

    if(state == Qt::Unchecked)
        dfcConcBox->setEnabled(false);
    else
        dfcConcBox->setEnabled(true);
}

void SimuUI::on_gcAccessBox_stateChanged(int state)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);
        
        if(state == Qt::Unchecked)
        {
            mols[id].GC_access = false;
            mols[id].GC_pourcentage = 0;
        }
        else
            mols[id].GC_access = true;
    }

    if(state == Qt::Unchecked)
        gcConcBox->setEnabled(false);
    else
        gcConcBox->setEnabled(true);
}

void SimuUI::on_movProbaBox_valueChanged(double c)
{
    if(selectMol->isChecked())
    {
        QTreeWidgetItem * current = molsWidget->currentItem();
    
        QString name = current->text(1);

        int id = molInList(name);
        
        mols[id].mov_proba = c;
    }
}

void SimuUI::simuIsDone(Results *resu)
{
    setLaunchButtonEnabled(true);
    emit signal_simuIsDone(resu);
}
