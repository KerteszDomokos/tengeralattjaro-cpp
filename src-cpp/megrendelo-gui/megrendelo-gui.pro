QT += core gui
QT += quickwidgets
QT += concurrent
QT += core
QT += network
QT += serialport
QT += charts
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    gui.cpp \
    settings.cpp \
    sockread.cpp\
    lejatszas.cpp

HEADERS += \
    gui.h \
    settings.h \
    sockread.h \
    lejatszas.h

FORMS += \
    gui.ui \
    settings.ui \
    lejatszas.ui

TRANSLATIONS += \
    megrendelo-gui_en_EN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



DISTFILES += \
    megrendelo-gui_en_EN.ts \
    qml-files/compass.qml \
    qml-files/horizon.qml \
    qml-files/compass \
    3d.qml

RESOURCES += \
    resource.qrc


win32: RC_ICONS = resources/program-icon.ico
