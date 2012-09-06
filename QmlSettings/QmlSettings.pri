QT += declarative
CONFIG += qt plugin

# Input
SOURCES += $$PWD/qmlsettings.cpp \
    $$PWD/qmlsettings_plugin.cpp

HEADERS +=  $$PWD/qmlsettings.h \
    $$PWD/qmlsettings_plugin.h

OTHER_FILES += $$PWD/qmldir
