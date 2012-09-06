#include "qmlsettings.h"

#include <QtDeclarative/qdeclarative.h>

QmlSettings::QmlSettings(QDeclarativeItem *parent):
    QDeclarativeItem(parent)
{
    ready = false;
}

QmlSettings::~QmlSettings()
{
}


void QmlSettings::initSettings(QString organization, QString application){
    organizationName = organization;
    applicationName = application;
    ready = true;
}

void QmlSettings::setOption(QString name, QVariant value){
    if(!ready)
        return;
    QSettings settings(organizationName, applicationName);
    settings.setValue(name, value);
    emit optionSetted();
}

void QmlSettings::getOption(QString name){
    if(!ready)
        return;
    QSettings settings(organizationName, applicationName);
    emit optionGetted(name, settings.value(name, false));
}
