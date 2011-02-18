/*
 * experimentui.cpp
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

#include "experimentui.h"

ExperimentUI::ExperimentUI(Experiment &_exp, QWidget *parent): ElementUI(parent)
{
    setupUi(this);
    
    exp = _exp;
    
    fillWidget();
}

void ExperimentUI::fillWidget()
{
    // General information
    idLabel->setText(exp["id"].toString());
    nameEdit->setText(exp["name"].toString());
    authorEdit->setText(exp["author"].toString());

    // Set date
    QDate date;
    if(exp["date"].toString() != "")
    {
        QStringList sdate = exp["date"].toString().split("-");
        date = QDate(sdate[0].toInt(), sdate[1].toInt(), sdate[2].toInt());
    }
    else
    {
        date = QDate::currentDate();
    }

    dateEdit->setDate(date);
    
    // Other info
    commentsEdit->setText(exp["comments"].toString());
    
    // Image gallery
    foreach(Image img, exp.getImages())
    {
        // TODO: regler pb du path quand on enrengistre une image
        ImageUI *imgui = new ImageUI(img);

        imgui->setParent(imgContainer);
        imgContainer->layout()->addWidget(imgui);

        imgContainer->show();

    }
}

void ExperimentUI::on_nameEdit_editingFinished()
{
    exp["name"] = nameEdit->text();
    emit expChanged(exp);
}

void ExperimentUI::on_authorEdit_editingFinished()
{
    exp["author"] = authorEdit->text();
    emit expChanged(exp);
}

void ExperimentUI::on_dateEdit_dateChanged(const QDate &date)
{
    exp["date"] = date.toString("yyyy-MM-dd");
    emit expChanged(exp);
}

void ExperimentUI::on_commentsEdit_textChanged()
{
    exp["comments"] = commentsEdit->toPlainText();
    emit expChanged(exp);
}

void ExperimentUI::on_removeButton_clicked()
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
        emit expRemove(exp);
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}
