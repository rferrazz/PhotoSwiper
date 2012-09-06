#include "qmlsettings_plugin.h"
#include "qmlsettings.h"

#include <QtDeclarative/qdeclarative.h>

void QmlSettingsPlugin::registerTypes(const char *uri)
{
    // @uri QmlSettings
    qmlRegisterType<QmlSettings>(uri, 1, 0, "QmlSettings");
}

Q_EXPORT_PLUGIN2(QmlSettings, QmlSettingsPlugin)

