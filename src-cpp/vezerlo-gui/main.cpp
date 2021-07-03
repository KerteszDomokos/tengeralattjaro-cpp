#define PY_SSIZE_T_CLEAN
#include "gui.h"

#include <QApplication>
#include <windows.h>
#include <QDebug>
#include <QThreadPool>
#include <QtConcurrent>

void komm(){
qDebug()<<"a";
Sleep(10000);
qDebug()<<"b";

}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFuture<void> future = QtConcurrent::run(komm);
    GUI w;
    w.show();
    qDebug() << "hello from GUI thread " << QThread::currentThread();
    future.waitForFinished();
    return a.exec();
}


