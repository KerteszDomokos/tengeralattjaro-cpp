#include "gui.h"
#include "ui_gui.h"

#include "sockread.h"

#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QDebug>
#include <thread>
#include <mutex>

#include <settings.h>

bool stop=0;

QString bejovo;
std::mutex bejovo_mutex;

SockRead sock;

void kommunikacio(){
    QString dat;
    QString elozoOlv;
    QList<double> sending;
    QList<double> sendingU;
    QString sendingS;
    long rsz=0;
    qDebug()<<"Kommunikációs szál indítása";
    while(true){
        if(stop==1){
            qDebug()<<"Leállítás";
            break;
        }
        Sleep(1);
        dat=sock.readS();
        if(dat!=elozoOlv && dat!=""){
            bejovo_mutex.lock();
            bejovo=dat;
            bejovo_mutex.unlock();
            elozoOlv=bejovo;
            qDebug()<<dat;
        }
    rsz++;
    if (rsz>2147483600){rsz=0;}
    }
}



GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    forditas("English");

    std::thread ob(kommunikacio);
    kommpointer=&ob;
    kommpointer->detach();

}

GUI::~GUI()
{
    delete ui;
}

void GUI::forditas(QString lang)
{
    qDebug()<<"Meghívva";
    if(lang=="English"){
        QTranslator translator;
        qDebug()<<translator.load(":/languages/megrendelo-gui_en_EN.qm");
        qApp-> QCoreApplication::installTranslator(&translator);
        qDebug()<<"Angol";
        ui->retranslateUi(this);
    }
    if(lang=="Magyar"){
    ui->retranslateUi(this);
    }

}

void GUI::open_beallitasok()
{
    set=new settings;
    set->show();
}

