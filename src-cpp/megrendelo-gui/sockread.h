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
        QString kuldoIP="169.254.15.251";
        QString vevoIP="169.254.62.249";

};


#endif // SOCKREAD_H
