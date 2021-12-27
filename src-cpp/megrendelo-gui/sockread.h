#ifndef SOCKREAD_H
#define SOCKREAD_H

#include <QUdpSocket>

class SockRead : public QObject{
        Q_OBJECT
    public:
        SockRead();
        QString readS();
        QByteArray readKep();
        void resetSettings();
        void applySettings(QString ip);

    private:
        QUdpSocket *socket;
        QUdpSocket *socketSend;
        QUdpSocket *socketKep;
        QString vevoIP="127.0.0.1";

};


#endif // SOCKREAD_H
