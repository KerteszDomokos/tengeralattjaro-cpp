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
        void megrSend(QList<double> dat);

    private:
        QUdpSocket *socket;
        QUdpSocket *socketSend;
        QUdpSocket *socketKep;
        QUdpSocket *sockMegr;
        QString kuldoIP="192.168.31.247";
        QString vevoIP="192.168.31.242";

        QString megrendeloIP="127.0.0.1";
        QString megrendeloKuldo="127.0.0.1";

};


#endif // SOCKREAD_H
