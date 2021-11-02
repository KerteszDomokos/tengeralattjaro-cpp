#include "gui.h"
#include "ui_gui.h"

#include "sockread.h"
#include <settings.h>

#include <thread>
#include <mutex>
#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QSizePolicy>
#include <QList>
#include <QSettings>


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
    sets = new QSettings("Aqualab megrendelő", "AquaLab");
    qRegisterMetaTypeStreamOperators<QList<bool> >("QList<int>");
    getUserdata();

    QApplication::setEffectEnabled(Qt::UI_AnimateCombo, false);

    set=new settings;

    kommdatUpdate();

    QTimer *kt = new QTimer(this);
    connect(kt, &QTimer::timeout, this, QOverload<>::of(&GUI::upd));
    kt->start(uptime);

    QTimer *friss = new QTimer(this);
    connect(friss, &QTimer::timeout, this, QOverload<>::of(&GUI::kommdatUpdate));
    friss->start(2);
    komm=1;
    kommst();

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

void GUI::applyUserdat()
{

    settingsOpened=0;
    frissites=set->getFrissites();
    kep=set->getKep();
    komm=set->getKomm();kommst();
    masiktema=set->getMasiktema();
    grid=set->getGrid();
    diagram=set->getDiagram();
    diagrammax=set->getDiagrammax();
    fileName=set->getFileName();
    language=set->getLanguage();
    ip=set->getIp();
    st=set->getSt();
    modename=set->getModename();

    //Mentendő adatok
    bdats={};
    bdats.append(frissites);//0
    bdats.append(kep);//1
    bdats.append(komm);//2
    bdats.append(komm);//3
    bdats.append(diagram);//4
    bdats.append(grid);//5
    bdats.append(masiktema);//6

    saveUserdat();
}

void GUI::saveUserdat(){
    sets->setValue("booldatas",QVariant::fromValue(bdats));
    sets->setValue("diagrammax",diagrammax);
    sets->setValue("fileName",fileName);
    sets->setValue("lang",language);
    sets->setValue("ip",ip);
    sets->setValue("Style",st);
}

void GUI::kommst()
{
    if(komm==0){
        stop=1;
    }else{
        if(stop==1){
            stop=0;
            std::thread ob(kommunikacio);
            kommpointer=&ob;
            kommpointer->detach();
        }
    }
}

void GUI::notapplyUserdat()
{
    qDebug()<<"notapply";
    settingsOpened=0;
}

void GUI::getUserdata()
{
    diagrammax=sets->value("diagrammax").toInt();
    fileName=sets->value("fileName").toString();
    language=sets->value("lang").toString();
    ip=sets->value("ip").toString();
    st=sets->value("Style").toString();
}

void GUI::forditas(QString lang)
{
    if(lang=="English"){
        QTranslator translator;
        qDebug()<<translator.load(":/languages/megrendelo-gui_en_EN.qm");
        qApp-> QCoreApplication::installTranslator(&translator);
        qDebug()<<"Angol";
        ui->retranslateUi(this);
    }
    if(lang=="Magyar"){
        qDebug()<<"Magyar";
    ui->retranslateUi(this);
    }
}

void GUI::open_beallitasok()
{
    if(settingsOpened==1){
        set->activateWindow();
    }else{
        delete set;
        set=new settings;
        settingsOpened=1;
        set->show();
        connect(set,SIGNAL(accepted()),this,SLOT(applyUserdat()));
        connect(set,SIGNAL(rejected()),this,SLOT(notapplyUserdat()));
    }
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
