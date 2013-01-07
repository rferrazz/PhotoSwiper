/*
* Photo Swiper
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
#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QSparqlQueryModel>
#include "qmlapplicationviewer.h"
#include "imagesender.h"
#include "QmlSettings/qmlsettings.h"
#include "PhotoPicker/photomodelbuilder.h"
#include "PhotoPicker/photoitem.h"

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
    qmlRegisterType<PhotoItem>("PhotoPicker", 1, 0, "PhotoItem");


    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("photomodel", PhotoModelBuilder::instance().model());
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/PhotoSwiper/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
