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
    felvetel.cpp \
    main.cpp \
    gui.cpp \
    sockread.cpp

HEADERS += \
    felvetel.h \
    gui.h \
    sockread.h

FORMS += \
    felvetel.ui \
    gui.ui


DISTFILES += \
    qml-files/3dview.qml \
    qml-files/compass.qml \
    qml-files/horizon.qml \
    qml-files/joy.qml \
    qml-files/magassag.qml \
    qml-files/map.qml \
    qml-files/teszt.qml \
    qml-files/radar.qml \
    qml-files/robotkar.qml


win32: RC_ICONS = resources/program-icon.ico

RESOURCES += \
    resource.qrc

CONFIG-=debug_and_release
DESTDIR = ./
