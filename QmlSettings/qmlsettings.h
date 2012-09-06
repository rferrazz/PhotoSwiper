#ifndef QMLSETTINGS_H
#define QMLSETTINGS_H

#include <QtDeclarative/QDeclarativeItem>
#include <QSettings>

class QmlSettings : public QDeclarativeItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QmlSettings)
    
public:
    QmlSettings(QDeclarativeItem *parent = 0);
    ~QmlSettings();

signals:
    void optionSetted();
    void optionGetted(QString optionName, QVariant optionValue);

public slots:
    void initSettings(QString organization, QString application);
    void setOption(QString name, QVariant value);
    void getOption(QString name);

private:
    QString organizationName;
    QString applicationName;
    bool ready;
};

QML_DECLARE_TYPE(QmlSettings)

#endif // QMLSETTINGS_H

