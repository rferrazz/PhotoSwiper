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
