/*
 * xmlaccess.cpp
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

#include <QtDebug>
#include <QtXmlPatterns>
#include <QDomNodeList>

#include "xmlaccess.h"

XmlAccess::XmlAccess(QString fname, QString fschema)
{
    // Opening database
    fdb.setFileName(fname);
    
    if(!(dbdoc.setContent(&fdb)))
    {
        qDebug() << "* Can't parse xml (database).";
    }

    // BUG : http://bugreports.qt.nokia.com/browse/QTBUG-6485
    // Load schema from fschema file and validate DB
    //this->schema.load(fschema);
    //this->valid = validate();

    // Get the root element
    root = dbdoc.documentElement();

    fdb.close();

    // Set all max ids
    setMaxId();

    // Set path 2 database
    path2db = QDir(fname);

}

XmlAccess::~XmlAccess()
{
}

void XmlAccess::setMaxId()
{

    // Get max id for molecules
    molMaxId = 0;
    QStringList ids = xquery("doc($url)//molecule/string(@id)");
    foreach(QString id, ids){
        if(molMaxId < id.toInt())
            molMaxId = id.toInt();
    }

    // Get max id for images
    imgMaxId = 0;
    ids = xquery("doc($url)//image/string(@id)");
    foreach(QString id, ids){
        if(imgMaxId < id.toInt())
            imgMaxId = id.toInt();
    }

    // Get max id for experiments
    expMaxId = 0;
    ids = xquery("doc($url)//experiment/string(@id)");
    foreach(QString id, ids){
        if(expMaxId < id.toInt())
            expMaxId = id.toInt();
    }

}

bool XmlAccess::validate()
{
    if (this->schema.isValid())
    {
        QXmlSchemaValidator validator(this->schema);
        if (validator.validate(this->dbdoc.toByteArray())){
            qDebug() << "* database is valid";
            return true;
        }
        else{
            qDebug() << "* database is invalid";
            return false;
        }
    }
    else{
        qDebug() << "* schema is invalid";
        return false;
    }
}

QStringList XmlAccess::xquery(QString frequest)
{

    QString request = frequest;
    
    // Opening database
    fdb.open(QIODevice::ReadOnly);

    query.bindVariable("url", QXmlItem(fdb.fileName()));
    query.setQuery("declare variable $url external;" +
                   request);
    
    QStringList results;
    if (query.isValid())
        query.evaluateTo(&results);
    else
        qDebug() << "* query is invalid";
    
    fdb.close();
    return results;
}

bool XmlAccess::getMolecule(int id, Molecule &gmol)
{
    foreach(Molecule mol, getMolecules())
    {
        if(mol["id"].toInt() == id)
        {
            gmol = mol;
            return true;
        }
    }
    return false;
}

bool XmlAccess::getExperiment(int id, Experiment &gexp)
{
    foreach(Experiment exp, getExperiments())
    {
        if(exp["id"].toInt() == id)
        {
            gexp = exp;
            return true;
        }
    }
    return false;
}

QList <Molecule> XmlAccess::getMolecules()
{
    QList <Molecule> elements;

    QDomElement type = this->root.firstChildElement();

    while(!type.isNull())
    {

        if(type.tagName() == "molecules")
        {
            QDomElement ele = type.firstChildElement();
            
            while(!ele.isNull())
            {
                QDomElement tag = ele.firstChildElement();
                Molecule mol;

                mol["id"] = ele.attribute("id");

                while(!tag.isNull())
                {
                    mol[tag.tagName()] = tag.text();
                    tag = tag.nextSiblingElement();
                }

                elements.append(mol);

                ele = ele.nextSiblingElement();
            }
        }
        
        type = type.nextSiblingElement();
    }
    return elements;
}

QList <Experiment> XmlAccess::getExperiments()
{
    QList <Experiment> elements;

    QDomElement type = this->root.firstChildElement();

    while(!type.isNull())
    {

        if(type.tagName() == "experiments")
        {
            QDomElement ele = type.firstChildElement();
            
            while(!ele.isNull())
            {
                QDomElement tag = ele.firstChildElement();
                Experiment exp;

                exp["id"] = ele.attribute("id");

                while(!tag.isNull())
                {
                    if (tag.tagName() == "images"){
                        QDomElement nimgs = tag.firstChildElement();
                        QList <Image> imgs;
                        
                        while(!nimgs.isNull())
                        {
                            QDomElement nimg = nimgs.firstChildElement();
                            Image img;
                            
                            img["id"] = nimgs.attribute("id");

                            while(!nimg.isNull())
                            {
                                if(nimg.tagName() == "path")
                                {
                                    QStringList path = path2db.path().split("/");
                                    path.pop_back();
                                    path.append(nimg.text());
                                    
                                    img[nimg.tagName()] = path.join("/");;
                                }
                                else
                                    img[nimg.tagName()] = nimg.text();
                                nimg = nimg.nextSiblingElement();
                            }
                            
                            imgs.append(img);
                            nimgs = nimgs.nextSiblingElement();
                        }
                        exp.setImages(imgs);
                    }
                    else{
                        exp[tag.tagName()] = tag.text();
                    }
                    tag = tag.nextSiblingElement();
                }

                elements.append(exp);

                ele = ele.nextSiblingElement();
            }
        }
        
        type = type.nextSiblingElement();
    }

    return elements;
}

int XmlAccess::addMolecule(Molecule mol)
{
    QDomElement ele = this->dbdoc.createElement("molecule");
    QDomElement parent = this->root.firstChildElement("molecules");
    
    int id;
    if(mol["id"].toString().length() > 0)
    {
        id = mol["id"].toInt();
    }
    else{
        id = ++molMaxId;
    }

    ele.setAttribute("id", id);
    
    QMapIterator<QString, QVariant> i(mol);
    while (i.hasNext()) {
        i.next();
        
        QDomElement n = this->dbdoc.createElement(i.key());
        QDomText nt;

        if(i.key() == "name" ||
           i.key() == "type" ||
           i.key() == "comments" ||
           i.key() == "embl_id" ||
           i.key() == "pdb_id" ||
           i.key() == "uniprotkb_id" ||
           i.key() == "sequence" ||
           i.key() == "sequence_length" ||
           i.key() == "default_concentration")
        {
            ele.appendChild(n);
            nt = this->dbdoc.createTextNode(i.value().toString());
            n.appendChild(nt);
        }
    }

    parent.appendChild(ele);

    return id;
}

int XmlAccess::addExperiment(Experiment exp)
{
    QDomElement nimgs = this->dbdoc.createElement("images");
    QDomElement ele = this->dbdoc.createElement("experiment");
    QDomElement parent = this->root.firstChildElement("experiments");
    
    int id;
    if(exp["id"].toString().length() > 0)
    {
        id = exp["id"].toInt();
    }
    else{
        id = ++expMaxId;
    }

    ele.setAttribute("id", id);
    
    QMapIterator<QString, QVariant> i(exp);
    while (i.hasNext()) {
        i.next();
        
        QDomElement n = this->dbdoc.createElement(i.key());
        QDomText nt;

        if(i.key() == "name" ||
           i.key() == "date" ||
           i.key() == "comments" ||
           i.key() == "author")
        {
            ele.appendChild(n);
            nt = this->dbdoc.createTextNode(i.value().toString());
            n.appendChild(nt);
        }
    }

    QList <Image> imgs = exp.getImages();
    if(!imgs.isEmpty()){
        foreach(Image img, imgs){

            QDomElement nimg = this->dbdoc.createElement("image");
            nimg.setAttribute("id", ++imgMaxId);

            QMapIterator<QString, QVariant> i(img);
            while (i.hasNext()) {
                i.next();
        
                QDomElement n = this->dbdoc.createElement(i.key());
                QDomText nt;

                if(i.key() == "name" ||
                   i.key() == "path" ||
                   i.key() == "comments")
                {
                    nt = this->dbdoc.createTextNode(i.value().toString());
                    n.appendChild(nt);
                }
                nimg.appendChild(n);
            }
            nimgs.appendChild(nimg);
        }
    }

    ele.appendChild(nimgs);
    parent.appendChild(ele);

    return id;
}

bool XmlAccess::removeMolecule(Molecule mol)
{
    bool re = false;

    QDomElement type = root.firstChildElement();

    while(!type.isNull())
    {
        if(type.tagName() == "molecules")
        {
            QDomNodeList domEle = root.elementsByTagName("molecule");

            if(!domEle.isEmpty())
            {
                for(uint i = 0; i < domEle.length(); i++)
                {
                    if(mol["id"] == domEle.at(i).toElement().attribute("id"))
                    {
                        type.removeChild(domEle.at(i));
                        re = true;
                    }
                }
            }
        }
        type = type.nextSiblingElement();
    }
    return re;
}

bool XmlAccess::removeExperiment(Experiment exp)
{
    bool re = false;

    QDomElement type = root.firstChildElement();

    while(!type.isNull())
    {
        if(type.tagName() == "experiments")
        {
            QDomNodeList domEle = root.elementsByTagName("experiment");

            if(!domEle.isEmpty())
            {
                for(uint i = 0; i < domEle.length(); i++)
                {
                    if(exp["id"] == domEle.at(i).toElement().attribute("id"))
                    {
                        type.removeChild(domEle.at(i));
                        re = true;
                    }
                }
            }
        }
        type = type.nextSiblingElement();
    }
    return re;
}

bool XmlAccess::modifMolecule(Molecule mol)
{
    removeMolecule(mol);
    addMolecule(mol);

    return true;
}

bool XmlAccess::modifExperiment(Experiment exp)
{
    removeExperiment(exp);
    addExperiment(exp);

    return true;
}

bool XmlAccess::save()
{
    if(this->fdb.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&(this->fdb));
        this->dbdoc.save(stream, true);
        this->fdb.close();
        return true;
    }
    else{
        qDebug() << "* can't save db";
        return true;
    }
}
