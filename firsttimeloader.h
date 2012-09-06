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
#ifndef FIRSTTIMELOADER_H
#define FIRSTTIMELOADER_H

#include <QObject>
#include <QThread>
#include <QList>
#include "constants.h"

class LoaderThread : public QThread
{
    Q_OBJECT
public:
    explicit LoaderThread(QList<QString> files, int size, QObject *parent = 0);
    void run();

signals:
    void thumbLoaded();

private:
    QList<QString> files;
    int size;
};

class FirstTimeLoader : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(FirstTimeLoader)
public:
    explicit FirstTimeLoader(QObject *parent = 0);
    
signals:
    void thumbLoaded();
    
public slots:
    void addThumb(QString file);
    void loadThumbs(int size);

private:
    QList<QString> *files;
    
};

#endif // FIRSTTIMELOADER_H
