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
#ifndef QMLSETTINGS_H
#define QMLSETTINGS_H

#include <QtDeclarative/QDeclarativeItem>
#include <QSettings>

class QmlSettings : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QmlSettings)
    
public:
    QmlSettings(QDeclarativeItem *parent = 0);
    ~QmlSettings();

signals:
    void optionSetted();
    void optionGetted(QString optionName, QVariant optionValue);

public slots:
    void initSettings(QString organization, QString application);
    void setOption(QString name, QVariant value);
    void getOption(QString name);

private:
    QString organizationName;
    QString applicationName;
    bool ready;
};

QML_DECLARE_TYPE(QmlSettings)

#endif // QMLSETTINGS_H

