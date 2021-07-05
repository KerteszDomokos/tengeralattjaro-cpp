#include "sockread.h"
#include <QDebug>
#include <QHostAddress>
#include <QUdpSocket>

SockRead::SockRead(){
socket = new QUdpSocket(this);
socket->bind(QHostAddress::LocalHost, 7755);
}
QString SockRead::readS()
{
        QByteArray buffer;
        buffer.resize(socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(buffer.data(), buffer.size(),
                             &sender, &senderPort);
//        qDebug() << "Message from: " << sender.toString();
//        qDebug() << "Message port: " << senderPort;
//        qDebug() << "Message: " << buffer;

        return buffer;
}

