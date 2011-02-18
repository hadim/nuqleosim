/*
 * moleculeui.cpp
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

#include "moleculeui.h"

#include "../utils/synchttp.h"

MoleculeUI::MoleculeUI(Molecule &_mol, QWidget *parent) : ElementUI(parent)
{
    setupUi(this);

    mol = _mol;
    
    // Set url to web database
    pdb_url = "http://www.pdb.org/pdb/files/@@@@.pdb";

    // Init widget
    typeList << "arn" << "adn" << "molecule";
    typeList << "ribosome" << "protein";
    foreach(QString e, typeList)
    {
        typeComboBox->addItem(e);
    }

    // Disable embl link
    emblBut->setEnabled(false);

    fillWidget();
}

void MoleculeUI::fillWidget()
{
    // General information
    idLabel->setText(mol["id"].toString());
    nameEdit->setText(mol["name"].toString());
    typeComboBox->setCurrentIndex(typeList.indexOf(mol["type"].toString()));
    lengthEdit->setText(mol["sequence_length"].toString());

    // Sequence
    sequenceEdit->setText(mol["sequence"].toString());
    
    // Other info
    concSpinBox->setValue(mol["default_concentration"].toDouble());
    commentsEdit->setText(mol["comments"].toString());
    
    // Web database links
    emblEdit->setText(mol["embl_id"].toString());
    uniprotkbEdit->setText(mol["uniprotkb_id"].toString());
    pdbEdit->setText(mol["pdb_id"].toString());

    // Disable button if no text in web database links
    if(pdbEdit->text() == "")
        pdbBut->setEnabled(false);
    if(uniprotkbEdit->text() == "")
        uniprotkbBut->setEnabled(false);
    if(emblEdit->text() == "")
        emblBut->setEnabled(false);

    // Create validator

    QRegExp rx("^.+$");
    QValidator *name_validator = new QRegExpValidator(rx, this);
    nameEdit->setValidator(name_validator);

    QValidator *length_validator = new QIntValidator(0, 99999999, this);
    lengthEdit->setValidator(length_validator);

}

void MoleculeUI::on_pdbBut_clicked()
{
    if(pdbEdit->text() != "")
    {
        QString links = "http://www.pdb.org/pdb/explore/explore.do?structureId=";
        links += pdbEdit->text();
        openEleBrowser(links);
    }
}

void MoleculeUI::on_emblBut_clicked()
{
    // if(emblEdit->text() != "")
    // {
    //     QString links = "http://www.pdb.org/pdb/explore/explore.do?structureId=";
    //     links += emblEdit->text();
    //     openEleBrowser(links);
    // }
}

void MoleculeUI::on_uniprotkbBut_clicked()
{
    if(uniprotkbEdit->text() != "")
    {
        QString links = "http://www.uniprot.org/uniprot/";
        links += uniprotkbEdit->text();
        openEleBrowser(links);
    }
}

void MoleculeUI::openEleBrowser(QString links)
{
    QDesktopServices::openUrl(QUrl(links, QUrl::TolerantMode));
}

void MoleculeUI::on_nameEdit_editingFinished()
{
    mol["name"] = nameEdit->text();
    emit molChanged(mol);
}

void MoleculeUI::on_typeComboBox_activated(const QString &text)
{
    mol["type"] = text;
    emit molChanged(mol);
}

void MoleculeUI::on_lengthEdit_editingFinished()
{
    mol["sequence_length"] = lengthEdit->text();
    emit molChanged(mol);
}

void MoleculeUI::on_concSpinBox_valueChanged(const QString &text)
{
    mol["default_concentration"] = text;
    emit molChanged(mol);
}

void MoleculeUI::on_sequenceEdit_textChanged()
{
    mol["sequence"] = sequenceEdit->toPlainText();
    emit molChanged(mol);
}

void MoleculeUI::on_pdbEdit_editingFinished()
{
    mol["pdb_id"] = pdbEdit->text();
    emit molChanged(mol);

    if(mol["pdb_id"].toString() == "")
        pdbBut->setEnabled(false);
    else
        pdbBut->setEnabled(true);
}

void MoleculeUI::on_emblEdit_editingFinished()
{
    mol["embl_id"] = emblEdit->text();
    emit molChanged(mol);

    // if(mol["embl_id"].toString() == "")
//        emblBut->setEnabled(false);
//    else
//        emblBut->setEnabled(true);
}

void MoleculeUI::on_uniprotkbEdit_editingFinished()
{
    mol["uniprotkb_id"] = uniprotkbEdit->text();
    emit molChanged(mol);

    if(mol["uniprotkb_id"].toString() == "")
        uniprotkbBut->setEnabled(false);
    else
        uniprotkbBut->setEnabled(true);
}

void MoleculeUI::on_commentsEdit_textChanged()
{
    mol["comments"] = commentsEdit->toPlainText();
    emit molChanged(mol);
}

void MoleculeUI::on_removeButton_clicked()
{
    int ret = QMessageBox::warning(this,
                                   tr("Remove current entry from database"),
                                   tr("Are you sure you want to remove this "
                                      "entry from database ?\n"
                                      "This action cannot be undo"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::No);
    
    switch (ret)
    {
    case QMessageBox::Yes:
        emit molRemove(mol);
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void MoleculeUI::on_pdbDownBut_clicked()
{
    // Open dialog to ask id pdb
    QString id_pdb = pdbEdit->text();
    
    Molecule tmp_mol;

    if(id_pdb == "")
    {
        QMessageBox::warning(this,
                             tr("No id pdb"),
                             tr("You need to enter at least one caracter "
                                "to be able to download a pdb file."),
                             QMessageBox::Close,
                             QMessageBox::Close);
    }
    else
    {
        pdbDownBut->setEnabled(false);

        // Download pdb file
        QUrl url(pdb_url.replace("@@@@", id_pdb));
        SyncHTTP h(url.host());
 
        statusLabel->setText(tr("Downloading is processing ..."));
        QTemporaryFile getOutput;
        getOutput.setAutoRemove(true);
        getOutput.open();
        h.syncGet(url.path(), &getOutput); 

        // Parse pdb file
        PDBParser yp;

        int id = mol["id"].toInt();
        tmp_mol = yp.getMolecule(getOutput.fileName())[0];

        if(tmp_mol["name"].toString().isEmpty())
        {
            QMessageBox::warning(this,
                                 tr("Wrong id pdb"),
                                 tr("This pdb id does not seem to exist "
                                    "in www.pdb.org."),
                                 QMessageBox::Close,
                                 QMessageBox::Close);
        }
        else
        {
            mol = tmp_mol;
            mol["id"] = QVariant(id);
            mol["pdb_id"] = id_pdb;

            fillWidget();
            emit molChanged(mol);
        }

        getOutput.setAutoRemove(true);
        getOutput.close();
        getOutput.remove();
        statusLabel->setText(tr(""));
        pdbDownBut->setEnabled(true);
    }
}
