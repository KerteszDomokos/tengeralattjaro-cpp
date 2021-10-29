#include "sockread.h"
#include <QDebug>
#include <QHostAddress>
#include <QUdpSocket>
#include <QNetworkDatagram>

SockRead::SockRead(){
socket = new QUdpSocket(this);
socketSend = new QUdpSocket(this);
socketKep = new QUdpSocket(this);
sockMegr = new QUdpSocket(this);

//socket->connectToHost(6010);
socket->bind(QHostAddress(vevoIP),6010);//vevő ezen eszköz ip címe
socketSend->connectToHost(QHostAddress(kuldoIP),6000);//küldő ip
sockMegr->connectToHost(QHostAddress(megrendeloKuldo),7000);
}
QString SockRead::readS()
{
    QByteArray buffer;
    qint16 s=socket->pendingDatagramSize();

    QNetworkDatagram datagram = socket->receiveDatagram(s);
    buffer=(datagram.data());
    return buffer;
}

bool SockRead::send(QList<double> dat)
{
    QByteArray byts;
    QString datS="[";

    for(int i=0; i<dat.size(); i++)
    {
        datS += QString::number(dat[i]);
        if(i<dat.size()-1)
        datS += "," ;
    }

    datS+="]";
    QTextStream in(&datS);
    byts=datS.toUtf8();
    socketSend->write(byts);
    return 1;
}

void SockRead::megrSend(QList<double> dat)
{
    QByteArray byts;
    QString datS="";

    for(int i=0; i<dat.size(); i++)
    {
        datS += QString::number(dat[i]);
        if(i<dat.size()-1)
        datS += " " ;
    }

    datS+="]";
    QTextStream in(&datS);
    byts=datS.toUtf8();
    socketSend->write(byts);
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

    kuldoIP="192.168.31.248";
    vevoIP="192.168.31.171";

}

void SockRead::applySettings()
{
    delete socket;
    delete socketSend;

    socket = new QUdpSocket(this);
    socketSend = new QUdpSocket(this);

    //socket->connectToHost(6010);
    socket->bind(QHostAddress(vevoIP),6010);//vevő ezen eszköz ip címe
    socketSend->connectToHost(QHostAddress(kuldoIP),6000);//küldő ip
}

