/*
* one line to give the program's name and an idea of what it does.
* Copyright (C) 2012  Riccardo Ferrazzo <f.riccardo87@gmail.com>

* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "firsttimeloader.h"
#include <QImage>

LoaderThread::LoaderThread(QList<QString> files, int size, QObject *parent) : QThread(parent)
{
    this->files = files;
    this->size = size;
}

void LoaderThread::run(){
    foreach(QString file, files){
    QString imgId = file;
    imgId.replace(QString("/"), QString(""));
    QImage thumb = QImage(file).scaled(QSize(size, size), Qt::KeepAspectRatioByExpanding);
    thumb.save(CACHE_FOLDER+imgId);
    emit thumbLoaded();
    }
    deleteLater();
}

FirstTimeLoader::FirstTimeLoader(QObject *parent) :
    QObject(parent)
{
    files = new QList<QString>();
}

void FirstTimeLoader::addThumb(QString file){
    files->push_back(file);
}

void FirstTimeLoader::loadThumbs(int size){
    LoaderThread *loader = new LoaderThread(*files, size, this);
    connect(loader, SIGNAL(thumbLoaded()), this, SIGNAL(thumbLoaded()));
    loader->start();
}
