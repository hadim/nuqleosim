/*
 * imageui.cpp
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

#include "imageui.h"

ImageUI::ImageUI(Image &_img) : QWidget()
{
    
    img = _img;

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(img["path"].toString()));
    scene->addItem(item);
        
    QGraphicsView *view = new QGraphicsView(scene);
    view->fitInView(0,0,1500,1500, Qt::KeepAspectRatioByExpanding);
    view->setParent(this);

}
