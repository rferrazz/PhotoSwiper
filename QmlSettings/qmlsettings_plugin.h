#ifndef QMLSETTINGS_PLUGIN_H
#define QMLSETTINGS_PLUGIN_H

#include <QDeclarativeExtensionPlugin>

class QmlSettingsPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
    
public:
    void registerTypes(const char *uri);
};

#endif // QMLSETTINGS_PLUGIN_H
