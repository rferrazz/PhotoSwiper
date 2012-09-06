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
#include "cachedimageprovider.h"

#include <QDir>

CachedImageProvider::CachedImageProvider() :
    QDeclarativeImageProvider(QDeclarativeImageProvider::Image)
{
    qDebug("entered");
    cache = new QHash<QString, QImage>();
    QDir cacheDir(CACHE_FOLDER);
    if (!cacheDir.exists()) {
        cacheDir.mkpath(".");
    }
    QList<QFileInfo> files = cacheDir.entryInfoList(QDir::Files);
    foreach(QFileInfo fi, files){
        cache->insert(fi.fileName(), QImage(fi.absoluteFilePath()));
    }
}

QImage CachedImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize){
    QString imgId = id;
    imgId.replace(QString("/"), QString(""));
    QImage result = cache->value(imgId);
    if(result.isNull()){
        result = QImage(id).scaled(QSize(requestedSize.width(), requestedSize.width()), Qt::KeepAspectRatioByExpanding);
        qDebug() << result.width();
        result.save(CACHE_FOLDER+imgId);
        cache->insert(imgId, result);
    }
    return result;
}
