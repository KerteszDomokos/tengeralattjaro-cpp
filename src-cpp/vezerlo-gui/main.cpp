#define PY_SSIZE_T_CLEAN
#include "gui.h"

#include <QApplication>
#include <windows.h>
#include <QDebug>
#include <QThreadPool>
#include <QtConcurrent>
#include <QSplashScreen>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);



    QPixmap pixmap(":/icons/logo");
    pixmap=pixmap.scaled(QSize(400,400));
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("AquaLab 2022 - loading interface");
//    Sleep(1000);//in production mode


    GUI w;
    w.show();
    splash.close();
    return a.exec();
}


