#include "gui.h"
#include "ui_gui.h"

#include <QDebug>
#include <QString>
#include <QTimer>
#include <QPixmap>
#include <QQuickWidget>
#include <QUrl>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQuickView>
#include <QTableView>
#include <QTableWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QThreadPool>
#include <QtConcurrent>
#include <QtConcurrentRun>
#include <QFuture>
#include <QProcess>
#include <QIODevice>
#include <QStringList>
#include <thread>
#include <mutex>
#include <QImage>
#include "sockread.h"
#include <cmath>

SockRead sock;

QByteArray kepadat;
std::mutex kepadat_mutex;

QString bejovo="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
std::mutex bejovo_mutex;

QList<double> kuldendo;
std::mutex kuldendo_mutex;


void read(){
    QString dat;
    QString elozoOlv;
    QList<double> sending; QString sendingS;
    long rsz;
    while(true){
        Sleep(1);
        dat=sock.readS();

        if(rsz%10==0){
            kuldendo_mutex.lock();
            sending=kuldendo;
            kuldendo_mutex.unlock();

            sock.send(sending);
        }

        if(dat!=elozoOlv && dat!=""){
            bejovo_mutex.lock();
            bejovo=dat;
            bejovo_mutex.unlock();
            elozoOlv=bejovo;

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

    QPixmap pm = QPixmap("..\\vezerlo-gui\\live.jpg"); // <- path to image file
    ui->horizont->setSource(QUrl::fromLocalFile("..\\vezerlo-gui\\horizon.qml"));

//    ui->hd->setSource(QUrl::fromLocalFile("../vezerlo-gui/3dview.qml"));
//    ui->hd->show();

    ui->joyh->setSource(QUrl::fromLocalFile("..\\vezerlo-gui\\joy.qml"));
    //QObject *object = ui->horizont->rootObject();

    ui->magmer->setSource(QUrl::fromLocalFile("../vezerlo-gui/magassag.qml"));
    ui->magmer->show();
    ui->ad->setPixmap(pm);
    ui->ad->setScaledContents(false);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::update));
    timer->start(6);
    QTimer *kt = new QTimer(this);
    connect(kt, &QTimer::timeout, this, QOverload<>::of(&GUI::fps));
    kt->start(10);

    //Joystick adatokat mentő program idítása

    QString file = "G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\joystick.py";
    pr->start("C:/Users/Gábor/AppData/Local/Programs/Python/Python38-32/python.exe", QStringList() << file);

    std::thread ob(read);
    ob.detach();


}

GUI::~GUI()
{
    pr->kill();//joystick folyamat befejezése
    pr->kill();//joystick folyamat befejezése
    pr->kill();//joystick folyamat befejezése

    delete ui;
}


void GUI::fps()
{
    QPixmap pm2 = QPixmap("..\\vezerlo-gui\\live.jpg"); // <- path to image file
    if (pm2.isNull()!=1){
        ui->ad->setPixmap(pm2);
        ui->ad->setScaledContents(false);
    }
}


void GUI::update()
{

    QImage kep;
    kep.loadFromData(kepadat);
    QPixmap pm=QPixmap::fromImage(kep);
    int sl;
    QString sliddat;
    sl = ui->slid1->value();
    sliddat = "Motor 1:\t"+ QString::number(sl);
    sl = ui->slid2->value();
    sliddat = sliddat +"\nMotor 2:\t" + QString::number(sl);
    sl = ui->slid3->value();
    sliddat = sliddat +"\nMotor közös:\t" + QString::number(sl);
    ui-> slidText->setText(sliddat);
    joydat();
    QList<double> jd=get_joystickAdatok();
    if(jd.isEmpty()==1){
        qDebug()<<"Üres joystickadatok";
    }else{
        /*ui->joystickdata->setItem(0, 0,new QTableWidgetItem(QString::number(joystickAdatok[0])));
        ui->joystickdata->setItem(0, 1,new QTableWidgetItem(QString::number(joystickAdatok[1])));
        ui->joystickdata->setItem(0, 2,new QTableWidgetItem(QString::number(joystickAdatok[2])));*/
        //ui->retranslateUi(this);
    }
//    qDebug()<<"Megváltoztatás után: "<<bejovo;


if(ui->tabWidget->currentIndex()==1){
    QObject *object = ui->joyh->rootObject();
    object->setProperty("b1", joystickAdatok[3]);
    object->setProperty("b2", joystickAdatok[4]);
    object->setProperty("b3", joystickAdatok[5]);
    object->setProperty("b4", joystickAdatok[6]);
    object->setProperty("b5", joystickAdatok[7]);
    object->setProperty("b6", joystickAdatok[8]);
    object->setProperty("b7", joystickAdatok[9]);
    object->setProperty("b8", joystickAdatok[10]);
    object->setProperty("b9", joystickAdatok[11]);
    object->setProperty("b10", joystickAdatok[12]);
    object->setProperty("b11", joystickAdatok[13]);
    object->setProperty("b12", joystickAdatok[14]);
    QString wrt="ElőreHátra:\n"+QString::number(joystickAdatok[1])+"\nJobbraBalra:\n"+QString::number(joystickAdatok[0])+"\nForgat:\n"+QString::number(joystickAdatok[2]);
    ui->joySzogadatok->setText(wrt);
}

bejovo_mutex.lock();
olvasott=conv(bejovo);
bejovo_mutex.unlock();
double dx;
double dy;
if (olvasott.size()>26){
    if(olvasott[22]>0){dx=std::sqrt(pow(olvasott[22]-90,2));}else{dx=-(olvasott[22]+90);}
    if(olvasott[23]>0){dy=std::sqrt(pow(olvasott[23]-90,2));}else{dy=-(olvasott[23]+90);}
    QObject *object = ui->horizont->rootObject();
    object->setProperty("pitchAngle", dx);//dőlés
    object->setProperty("rollhAngle", dy);//forgás

}





if(ui->tabWidget->currentIndex()==0 || olvasott!=elozoOlvasottList){
    QString string;
    elozoOlvasottList=olvasott;
    for(int i=0; i<olvasott.size(); i++)
    {
        string += QString::number(olvasott[i]);
        if(i<olvasott.size()-1)
        string += "," ;
    }
    ui->nyersOlvasott->setText(string);
    if(olvasott.size()>26){
    ui->foadatok_1->setItem(0,0, new QTableWidgetItem(QString::number(0)));//sebesség
    ui->foadatok_1->setItem(0,1, new QTableWidgetItem(QString::number(dx)));//dőlés x
    ui->foadatok_1->setItem(0,2, new QTableWidgetItem(QString::number(dy)));//dőlés y
    ui->foadatok_1->setItem(0,3, new QTableWidgetItem(QString::number(olvasott[9])));//motorB
    ui->foadatok_1->setItem(0,4, new QTableWidgetItem(QString::number(olvasott[10])));//motorJ
    ui->foadatok_1->setItem(0,5, new QTableWidgetItem(QString::number(olvasott[26])));//test iránya
    ui->foadatok_2->setItem(0,0, new QTableWidgetItem(QString::number(0)));//döntőmotor felső
    ui->foadatok_2->setItem(0,1, new QTableWidgetItem(QString::number(0)));//alsó
    ui->foadatok_2->setItem(0,2, new QTableWidgetItem(QString::number(0)));//vízhőm
    ui->foadatok_2->setItem(0,3, new QTableWidgetItem(QString::number(0)));//wifi jelerősség
    ui->foadatok_2->setItem(0,4, new QTableWidgetItem(QString::number(olvasott[12])));//nyomás
    ui->foadatok_2->setItem(0,5, new QTableWidgetItem(QString::number(olvasott[0])));//sikerese a komm
    ui->foadatok_3->setItem(0,0, new QTableWidgetItem(QString::number(olvasott[5])));//belső hőm
    ui->foadatok_3->setItem(0,1, new QTableWidgetItem(QString::number(olvasott[7])));//DHT hőm
    ui->foadatok_3->setItem(0,2, new QTableWidgetItem(QString::number(olvasott[8])));//páratart
    ui->foadatok_3->setItem(0,3, new QTableWidgetItem(QString::number(olvasott[1])));//belső víz
    ui->foadatok_3->setItem(0,4, new QTableWidgetItem(QString::number(olvasott[21])));//rpi proc
    ui->foadatok_3->setItem(0,5, new QTableWidgetItem(QString::number(olvasott[20])));// serbuff fedélzet
    ui->foadatok_4->setItem(0,0, new QTableWidgetItem(QString::number(olvasott[11])));//5vakk1 raspi akku
    ui->foadatok_4->setItem(0,1, new QTableWidgetItem(QString::number(olvasott[13])));//12vakku1 motor
    ui->foadatok_4->setItem(0,2, new QTableWidgetItem(QString::number(0)));//5v masodlagos
    ui->foadatok_4->setItem(0,3, new QTableWidgetItem(QString::number(0)));//12v masodlagos
    ui->foadatok_4->setItem(0,4, new QTableWidgetItem(QString::number(olvasott[4])));//csp1
    ui->foadatok_4->setItem(0,5, new QTableWidgetItem(QString::number(0)));//csp2
//    qDebug()<<olvasott;



    QObject *object2 = ui->magmer->rootObject();
    object2->setProperty("alt", olvasott[12]*10);//magasság
}
}

if (ui->motegy->isChecked()==1){
    int val=ui->slid3->value();
    ui->slid1->setValue(val);
    ui->slid2->setValue(val);
}


QList<double> idl;

idl.append(0);//0 használatlan
idl.append(ui->slid2->value());//1 motor2 érték
idl.append(0);//2 mélységmérés
idl.append(0);//3 tápegység állapot
idl.append(0);//4 ballaszttartály1 állapot
idl.append(0);//5 ballaszttartály2 állapot
idl.append(ui->slid6->value());//6 hűtőventillátor
idl.append(0);//7 bal vezérsík - üres
idl.append(0);//8 jobb vezérsík - üres
idl.append(0);//9 motor reset kérés
idl.append(ui->slid1->value());//10 motor1 %
idl.append(ui->slid4->value());//11 Navigációs motor felső
idl.append(ui->slid5->value());//12 Navigációs motor alsó
idl.append(0);//13 SSH reset kérés
idl.append(0);//14 Küldés időpontja
idl.append(0);//15 robotkar adatok ...
idl.append(0);//16 robotkar adatok ...
idl.append(0);//17 robotkar adatok ...
idl.append(0);//18 robotkar adatok ...
idl.append(0);//19 robotkar adatok ...
idl.append(0);//20 robotkar adatok ...
idl.append(0);//20 robotkar adatok ...
idl.append(0);//22 robotkar adatok ...
idl.append(0);//23 robotkar adatok ...
idl.append(0);//24 robotkar adatok ...
idl.append(0);//25 robotkar adatok ...
idl.append(0);//26 robotkar adatok ...

//qDebug()<<idl;


kuldendo_mutex.lock();
kuldendo=idl;
kuldendo_mutex.unlock();



}

void GUI::cmdSlot()
{
    QString readedT = ui->cmd_p->text();
    QString newline="\n";
    QString ures="";
    ui->cmd_p->show();
    qDebug() <<"Beírt parancs:"<< readedT;
    ui->cmd_p-> setText(ures);
    QString regiT = ui->command->toPlainText();
    ui->command-> setText(commands(readedT));
}

void GUI::openCmd()
{

    qDebug()<<"cmd megnyitása";
    ui->cmdDock->show();
    ui->cmdDock->activateWindow();
    ui->cmd_p->cursorWordForward(1);
}

void GUI::closeCmd()
{
    qDebug()<<"cmd bezárása";
    ui->cmdDock->setHidden(1);
}

QString GUI::commands(QString comm)
{
    if (comm=="comm"){
        return "Parancs végrehajtása siekeres";
    }
    else if(comm=="exit"){
        close();
        return "Kilépés...";
    }
    else if(comm=="readUdp"){
        read();
        return"Parancssoron az eredmény";
    }

    return "Nem található a kért parancs: "+comm;
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

void GUI::joydat()
{
    QList<double> array;

    QFile file("../vezerlo-gui/joystick.txt");

    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Error in file read";
        QMessageBox::information(0, "error", file.errorString());
        return;
        }
    QString str;

    QTextStream in(&file);
    str = in.readLine();
    if (str!=""){
        QTextStream stream(&str);
        while (!stream.atEnd()) {
            double number;
            stream >> number;
            array.append(number);
        }
        if (array.isEmpty()==0){
            joystickAdatok=array;
        }
    }
    return;
}
QList<double> GUI::get_joystickAdatok()
{
    return joystickAdatok;
}


