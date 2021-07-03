#include "kommunikacio.h"

#include <QDebug>
#include <windows.h>

Kommunikacio::Kommunikacio()
{

}

void Kommunikacio::run()
{
    qDebug()<<"a";
    Sleep(10000);
    qDebug()<<"b";

}
