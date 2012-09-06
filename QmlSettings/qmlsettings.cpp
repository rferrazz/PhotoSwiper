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
#include "qmlsettings.h"

#include <QtDeclarative/qdeclarative.h>

QmlSettings::QmlSettings(QDeclarativeItem *parent):
    QDeclarativeItem(parent)
{
    ready = false;
}

QmlSettings::~QmlSettings()
{
}


void QmlSettings::initSettings(QString organization, QString application){
    organizationName = organization;
    applicationName = application;
    ready = true;
}

void QmlSettings::setOption(QString name, QVariant value){
    if(!ready)
        return;
    QSettings settings(organizationName, applicationName);
    settings.setValue(name, value);
    emit optionSetted();
}

void QmlSettings::getOption(QString name){
    if(!ready)
        return;
    QSettings settings(organizationName, applicationName);
    emit optionGetted(name, settings.value(name, false));
}
