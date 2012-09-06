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
#include "imagesender.h"

#include <QTimer>

SocketThread::SocketThread(QHostAddress address, int port, QImage data, QObject *parent) :
    QThread(parent)
{
    socket = new QTcpSocket();
    raw_data = new QByteArray();
    QBuffer buffer(raw_data);
    data.save(&buffer, "JPG");
    socket->connectToHost(address, port);
}

void SocketThread::run(){
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << (qint64)0;
    out << *raw_data;
    out.device()->seek(0);
    out << (qint64)(datagram.size() - sizeof(qint64));
    socket->write(datagram);
    emit dataSent();
}

ImageSender::ImageSender(QObject *parent) :
    QObject(parent)
{
    threadPool = QThreadPool::globalInstance();
    lastPort = 6017;
    adresses = new QHash<QHostAddress, int>();
    mdns = new JDnsShared(JDnsShared::Multicast);
    mdns->addInterface(QHostAddress::Any);
    request = new JDnsSharedRequest(mdns);
    requestTimer = new QTimer(this);
    requestTimer->setInterval(1000);
    connect(request, SIGNAL(resultsReady()), this, SLOT(dnsResults()));
    connect(requestTimer, SIGNAL(timeout()), this, SLOT(sendRequest()));
    requestTimer->start();
}

void ImageSender::dnsResults(){
    if(request->success()){
        QList<QJDns::Record> results = request->results();
        switch(results[0].type){
        case QJDns::Ptr:
            requestTimer->stop();
            request->query(results[0].name, QJDns::Srv);
            break;
        case QJDns::Srv:
            if(results[0].port != 0)
                lastPort = results[0].port;
            request->query(results[0].name, QJDns::A);
            break;
        case QJDns::A:
            if(!adresses->contains(results[0].address))
                adresses->insert(results[0].address, lastPort);
        }
    }
}

void ImageSender::sendRequest(){
    request->query("_imageserver._tcp.local", QJDns::Ptr);
}

void ImageSender::sendImage(QString imageLocation, int height){
    QImage image(imageLocation);
    if(height > 0){
        image = image.scaledToHeight(height);
    }
    QList<QHostAddress> keys = adresses->keys();
    foreach(QHostAddress host, keys){
        SocketThread *st = new SocketThread(host, adresses->value(host), image, this);
        connect(st, SIGNAL(dataSent()), this, SIGNAL(imageSent()));
        st->start();
    }
}
