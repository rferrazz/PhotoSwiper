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
#ifndef IMAGESENDER_H
#define IMAGESENDER_H

#include <QObject>
#include <QImage>
#include <QTimer>
#include "jdns/jdnsshared.h"

class SocketThread : public QThread
{
    Q_OBJECT
public:
    explicit SocketThread(QHostAddress address, int port, QImage data, QObject *parent = 0);
    void run();

signals:
    void dataSent();

private:
    QByteArray *raw_data;
    QTcpSocket *socket;
};

class ImageSender : public QObject
{
    Q_OBJECT
public:
    explicit ImageSender(QObject *parent = 0);
    
signals:
    void addressAdded();
    void imageSent();
    
public slots:
    void sendImage(QString imageLocation, int height);
    void setReciver(QString adress, int port);

private slots:
    void dnsResults();
    void sendRequest();

private:
    JDnsShared *mdns;
    JDnsSharedRequest *request;
    int lastPort;
    QHash<QHostAddress, int> *adresses;
    QThreadPool *threadPool;
    QTimer *requestTimer;
};

#endif // IMAGESENDER_H
