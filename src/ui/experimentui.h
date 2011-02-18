/*
 * experimentui.h
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

#ifndef HEADER_EXPERIMENTUI
#define HEADER_EXPERIMENTUI

#include <QtGui>
#include "ui_experimentui.h"

#include "elementui.h"
#include "imageui.h"

#include "../datamodel/molecule.h"
#include "../datamodel/image.h"
#include "../datamodel/experiment.h"

class ExperimentUI : public ElementUI, private Ui::ExperimentUI
{
    Q_OBJECT

public:
    ExperimentUI(Experiment &_exp, QWidget *parent = 0);

private:
    Experiment exp;
    QLabel *t;

    void fillWidget();

private slots:
    void on_nameEdit_editingFinished();
    void on_authorEdit_editingFinished();
    void on_dateEdit_dateChanged(const QDate &date );
    void on_commentsEdit_textChanged();

    void on_removeButton_clicked();

signals:
    void expChanged(Experiment &exp);
    void expRemove(Experiment &exp);
};

#endif
