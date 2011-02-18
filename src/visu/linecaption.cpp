/*
 * linecaption.cpp
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

#include "linecaption.h"

LineCaption::LineCaption(QString name,
                         int r, int g, int b,
                         QWidget *parent)
{
    setupUi(this);

    nameLabel->setText(name);
    nameLabel->setWordWrap(true);

    colorLabel->setText("      ");
    QString style = QString("QLabel { background: rgb(%1, %2, %3); }").arg(r).arg(g).arg(b);
    colorLabel->setStyleSheet(style);

    // QPalette p = colorLabel->palette();
//     p.setColor(QPalette::Background, QColor(r, g, b));
//     colorLabel->setPalette(p);

    
    update();
}
