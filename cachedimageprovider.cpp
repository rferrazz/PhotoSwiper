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
