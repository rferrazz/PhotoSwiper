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
