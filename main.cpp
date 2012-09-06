#include <QtGui/QApplication>
#include <QtDeclarative>
#include "qmlapplicationviewer.h"
#include "imagesender.h"
#include "cachedimageprovider.h"
#include "QmlSettings/qmlsettings.h"
#include "firsttimeloader.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QNetworkConfigurationManager manager;
    QNetworkConfiguration cfg = manager.defaultConfiguration();
    QNetworkSession* session = new QNetworkSession(cfg);
    session->setSessionProperty("ConnectInBackground", false);
    session->open();

    qmlRegisterType<ImageSender>("QmlSharing", 1, 0, "ImageSender");
    qmlRegisterType<QmlSettings>("QmlSettings", 1, 0, "Settings");
    qmlRegisterType<FirstTimeLoader>("QmlSharing", 1, 0, "FirstTimeLoader");

    QmlApplicationViewer viewer;
    viewer.engine()->addImageProvider("cache", new CachedImageProvider());
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/PhotoSwiper/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
