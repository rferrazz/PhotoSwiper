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
#ifndef CACHEDIMAGEPROVIDER_H
#define CACHEDIMAGEPROVIDER_H

#include <QDebug>
#include <QDeclarativeImageProvider>
#include <QImage>
#include <QHash>
#include "constants.h"

class CachedImageProvider : public QDeclarativeImageProvider
{
    Q_DISABLE_COPY(CachedImageProvider)
public:
    explicit CachedImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    
signals:
    
public slots:

private:
    QHash<QString, QImage> *cache;
    
};

#endif // CACHEDIMAGEPROVIDER_H
