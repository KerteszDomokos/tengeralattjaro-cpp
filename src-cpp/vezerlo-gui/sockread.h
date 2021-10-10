#ifndef SOCKREAD_H
#define SOCKREAD_H

#include <QUdpSocket>

class SockRead : public QObject{
        Q_OBJECT
    public:
        SockRead();
        QString readS();
        bool send(QList<double> dat);
        QByteArray readKep();
        void resetSettings();
        void applySettings();

    private:
        QUdpSocket *socket;
        QUdpSocket *socketSend;
        QUdpSocket *socketKep;
        QString kuldoIP="192.168.31.248";
        QString vevoIP="192.168.31.171";

};


#endif // SOCKREAD_H
