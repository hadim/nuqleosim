/*
 * settingsui.h
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

#ifndef HEADER_SETTINGSUI
#define HEADER_SETTINGSUI

#include <QtGui>
#include "ui_settingsui.h"

class SettingsUI : public QDialog, private Ui::SettingsUI
{
    Q_OBJECT

public:
    SettingsUI(QSettings *_settings, QWidget *parent = 0);

private:
    QSettings *settings;

    void fillWidget();
    void writeSettings();

private slots:
    void on_databaseButton_clicked();
    void on_schemaButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};


#endif
