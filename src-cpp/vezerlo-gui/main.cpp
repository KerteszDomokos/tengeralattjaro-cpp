#define PY_SSIZE_T_CLEAN
#include "gui.h"

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
    return a.exec();
}


