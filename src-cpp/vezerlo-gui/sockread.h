#ifndef SOCKREAD_H
#define SOCKREAD_H

#include <QUdpSocket>

class SockRead : public QObject{
        Q_OBJECT
    public:
        SockRead();
        QString readS();

    private:
        QUdpSocket *socket;

};


#endif // SOCKREAD_H
