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
