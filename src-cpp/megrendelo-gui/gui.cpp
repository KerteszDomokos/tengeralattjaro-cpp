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
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QSizePolicy>
#include <QList>

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
    kt->start(uptime);

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

    double bmot=0;
    double jmot=0;
    if(olvasottList.length()>15){
        bmot=olvasottList[9];
        jmot=olvasottList[10];
        ui->balmot->setText(QString::number(bmot));
        ui->jobbmot->setText(QString::number(jmot));
        ui->bhom->setText(QString::number(olvasottList[7]));
    }
    UID++;
    ui->uid->setText(QString::number(UID));

    if(ido.length()<100){
        ido.append(double(UID)/(1000/uptime));//másodperc
    }else{
        for (int i=0;i<99;i++){
           ido[i]=ido[i+1];
        }
        ido[99]=double(UID)/(1000/uptime);
    }
    if(motatlag.length()<100){
        motatlag.append((bmot+jmot)/2);//átlag
    }else{
        for (int i=0;i<99;i++){
            motatlag[i]=motatlag[i+1];
        }
        motatlag[99]=(bmot+jmot)/2;
    }

}

void GUI::loadGraf()
{
    qDebug()<<"loadGraf()";
    QLineSeries *series=new QLineSeries();

    xteng=ido;
    yteng=motatlag;

    for (int i=0; i<50 && i<xteng.length()-1 && i<yteng.length()-1;i++){
        series->append(xteng[i],yteng[i]);
    }


    QChart *chart = new QChart();
    //chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Grafikon");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignCenter);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->graf);
    chartView->setMaximumSize(ui->graf->size());
    chartView->setMinimumSize(ui->graf->size());
    chartView->maximumSize();
    chartView->show();

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
