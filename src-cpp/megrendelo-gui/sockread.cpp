#include "sockread.h"
#include <QDebug>
#include <QHostAddress>
#include <QUdpSocket>
#include <QNetworkDatagram>

SockRead::SockRead(){
socket = new QUdpSocket(this);

//socket->connectToHost(6010);
socket->bind(QHostAddress(vevoIP),7000);//vevő ezen eszköz ip címe


}
QString SockRead::readS()
{
    QByteArray buffer;
    qint16 s=socket->pendingDatagramSize();

    QNetworkDatagram datagram = socket->receiveDatagram(s);
    buffer=(datagram.data());
    return buffer;
}



QByteArray SockRead::readKep()
{
    QByteArray buffer;
    qint16 s=socketKep->pendingDatagramSize();

    QNetworkDatagram datagram = socketKep->receiveDatagram(s);

    buffer=(datagram.data());
//    qDebug ()<<buffer.toHex();
    return buffer.toHex();
}

void SockRead::resetSettings()
{

    vevoIP="127.0.0.1";

}

void SockRead::applySettings(QString ip)
{
    delete socket;

    socket = new QUdpSocket(this);

    //socket->connectToHost(6010);
    socket->bind(QHostAddress(vevoIP),7000);//vevő ezen eszköz ip címe
}

