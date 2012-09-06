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
    void imageSent();
    
public slots:
    void sendImage(QString imageLocation, int height);

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
