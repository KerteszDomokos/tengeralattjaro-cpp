#include "gui.h"
#include "ui_gui.h"

#include "sockread.h"

#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QDebug>
#include <thread>
#include <mutex>
#include <QTimer>

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
            elozoOlv=dat;
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

    QApplication::setEffectEnabled(Qt::UI_AnimateCombo, false);


    kommdatUpdate();

    QTimer *kt = new QTimer(this);
    connect(kt, &QTimer::timeout, this, QOverload<>::of(&GUI::upd));
    kt->start(30);

    QTimer *friss = new QTimer(this);
    connect(friss, &QTimer::timeout, this, QOverload<>::of(&GUI::kommdatUpdate));
    friss->start(2);

    std::thread ob(kommunikacio);
    kommpointer=&ob;
    kommpointer->detach();

}

GUI::~GUI()
{
    delete ui;
}

void GUI::upd()
{
    if(olvasottNat!=""){ olvasottList=conv(olvasottNat);}


    if(olvasottList.length()>15){
        ui->balmot->setText(QString::number(olvasottList[9]));
        ui->jobbmot->setText(QString::number(olvasottList[10]));
        ui->bhom->setText(QString::number(olvasottList[7]));
    }
    UID++;
    ui->uid->setText(QString::number(UID));

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

void GUI::kommdatUpdate()
{
    bejovo_mutex.lock();
    olvasottNat=bejovo;
    bejovo_mutex.unlock();
}


//Szünettel elválasztott szöveget konvertál QList doubel ba
QList<double> GUI::conv(QString str){
    QTextStream stream(&str);
    QList<double> array;
    while (!stream.atEnd()) {
        double number;
        stream >> number;
        array.append(number);
    }
    return array;
}

void GUI::kommentMost()
{
    ui->mostID->setText(QString::number(UID));
    commentID=UID;
}
