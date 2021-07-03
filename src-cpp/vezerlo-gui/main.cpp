#define PY_SSIZE_T_CLEAN
#include "gui.h"
#include "kommunikacio.h"

#include <QApplication>
#include <windows.h>
#include <QDebug>
#include <QThreadPool>
#include <QtConcurrent>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI w;
    w.show();
    Kommunikacio th;
    th.start();
    qDebug() << "hello from GUI thread " << QThread::currentThread();
    return a.exec();
}


