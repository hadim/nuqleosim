/*
 * moleculeui.h
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

#ifndef HEADER_MOLECULEUI
#define HEADER_MOLECULEUI

#include <QtGui>
#include <QDesktopServices>
#include <QtNetwork>

#include "ui_moleculeui.h"

#include "elementui.h"

#include "../datamodel/molecule.h"
#include "../parser/PDBParser.h"

class MoleculeUI : public ElementUI, private Ui::MoleculeUI
{
    Q_OBJECT

public:
    MoleculeUI(Molecule &_mol, QWidget *parent = 0);

private:
    Molecule mol;
    QStringList typeList;
    void openEleBrowser(QString links);
    void fillWidget();

    QString pdb_url;

private slots:
    void on_pdbBut_clicked();
    void on_emblBut_clicked();
    void on_uniprotkbBut_clicked();

    void on_nameEdit_editingFinished();
    void on_typeComboBox_activated(const QString &text);
    void on_lengthEdit_editingFinished();
    void on_concSpinBox_valueChanged(const QString &text);
    void on_sequenceEdit_textChanged();
    void on_pdbEdit_editingFinished();
    void on_emblEdit_editingFinished();
    void on_uniprotkbEdit_editingFinished();
    void on_commentsEdit_textChanged();

    void on_removeButton_clicked();
    void on_pdbDownBut_clicked();
    
signals:
    void molChanged(Molecule &mol);
    void molRemove(Molecule &mol);
    
};

#endif
