/*
 * settingsui.cpp
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

#include "settingsui.h"

SettingsUI::SettingsUI(QSettings *_settings,
                       QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    settings = _settings;
    
    // Fill the widget
    fillWidget();
}

void SettingsUI::fillWidget()
{
    
    // Database
    settings->beginGroup("database");
    {
        databaseEdit->setText(settings->value("default_db").toString());
        schemaEdit->setText(settings->value("default_schema").toString());
    }
    settings->endGroup();
}

void SettingsUI::writeSettings()
{
    
    // Database
    settings->beginGroup("database");
    {
        settings->setValue("default_db", databaseEdit->text());
        settings->setValue("default_schema", schemaEdit->text());
    }
    settings->endGroup();

}

void SettingsUI::on_databaseButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Database"),
                                                QDir::homePath(),
                                                tr("NQS database (*.xml)"));
    databaseEdit->setText(file);
}

void SettingsUI::on_schemaButton_clicked()
{
    


}

void SettingsUI::on_buttonBox_accepted()
{
    hide();
    writeSettings();
}

void SettingsUI::on_buttonBox_rejected()
{
    hide();
    fillWidget();
}
