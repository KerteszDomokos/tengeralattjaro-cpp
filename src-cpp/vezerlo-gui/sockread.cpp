#include "sockread.h"
#include <QDebug>
#include <QHostAddress>
#include <QUdpSocket>
#include <QNetworkDatagram>

SockRead::SockRead(){
socket = new QUdpSocket(this);

//socket->connectToHost(6010);
socket->bind(QHostAddress("192.168.31.169"),6010);

}
QString SockRead::readS()
{
        QByteArray buffer;
//        buffer.resize(socket->pendingDatagramSize());

        QHostAddress sender;
//        quint16 senderPort;
        qint16 s=socket->pendingDatagramSize();

           QNetworkDatagram datagram = socket->receiveDatagram(s);
           buffer=(datagram.data());

//        socket->readDatagram(buffer.data(), buffer.size(),
//                             &sender, &senderPort);
//        qDebug() << "Message from: " << sender.toString();
//        qDebug() << "Message port: " << senderPort;
//          qDebug() << "Message: " << buffer;

        return buffer;
}

