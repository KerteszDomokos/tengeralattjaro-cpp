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
#include <QTextCursor>
#include <QSerialPort>
#include <QSerialPortInfo>

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


    ui->horizont->setSource(QUrl::fromLocalFile("..\\vezerlo-gui\\qml-files\\horizon.qml"));
    ui->joyh->setSource(QUrl::fromLocalFile("..\\vezerlo-gui\\qml-files\\joy.qml"));
    ui->magmer->setSource(QUrl::fromLocalFile("../vezerlo-gui/qml-files/magassag.qml"));
    ui->compass->setSource(QUrl::fromLocalFile("../vezerlo-gui/qml-files/compass.qml"));
//    ui->map->setSource(QUrl::fromLocalFile("../vezerlo-gui/map.qml"));

    QPixmap pm = QPixmap("..\\vezerlo-gui\\program-datas\\live.jpg"); // <- path to image file
    ui->ad->setPixmap(pm);
    ui->ad->setScaledContents(false);


    QTimer *timer = new QTimer(this);//időzítők
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::update));
    timer->start(6);

    QTimer *kt = new QTimer(this);
    connect(kt, &QTimer::timeout, this, QOverload<>::of(&GUI::fps));
    kt->start(30);


    QTimer *jd = new QTimer(this);
    connect(jd, &QTimer::timeout, this, QOverload<>::of(&GUI::joydat));
    jd->start(1000*0.005);

    //Joystick adatokat mentő program idítása
    pr = new QProcess(this);
    QString file = joypath;
    pr->start(pypath, QStringList() << file);

    //Kép adatokat mentő program indítása
    pr2 = new QProcess(this);
    file = keppath;
    pr2->start(pypath, QStringList() << file);

    ui->joyPID->setText(QString::number(pr->processId()));
    ui->kepPID->setText(QString::number(pr2->processId()));
    ui->joyPID->setStyleSheet("QLineEdit {background-color: green;}");
    ui->kepPID->setStyleSheet("QLineEdit {background-color: green;}");

    //szál indítása
    std::thread ob(read);
    ob.detach();

    ui->elokep->setChecked(1);
    ui->cmdDock->setHidden(1);

    mSerial = new QSerialPort(this);

    connect(mSerial, &QSerialPort::readyRead,
            this, &GUI::serkom);





}

GUI::~GUI()
{
    mSerial->close();
    delete ui;
    pr->kill();//joystick folyamat befejezése
    pr2->kill();//kép folyamat befejezése

}


void GUI::fps()
{
    QPixmap pm2 = QPixmap("..\\vezerlo-gui\\program-datas\\live.jpg"); // <- path to image file
    if (pm2.isNull()!=1){//ha a kép létezik:
        ui->ad->setPixmap(pm2);
        ui->ad->setScaledContents(false);
    }


    //Külső folyamatok sikerességére vonatkozó adatok
    int pid=pr->processId();
    ui->joyPID->setText(QString::number(pid));
    if (pid==0){ui->joyPID->setStyleSheet("QLineEdit {background-color: red;}");}else{ui->joyPID->setStyleSheet("QLineEdit {background-color: green;}");}
    pid=pr2->processId();
    ui->kepPID->setText(QString::number(pid));
    if (pid==0){ui->kepPID->setStyleSheet("QLineEdit {background-color: red;}");}else{ui->kepPID->setStyleSheet("QLineEdit {background-color: green;}");}
}


void GUI::update()
{

    QList<double> jd=get_joystickAdatok();
    if(jd.isEmpty()==1){
        qDebug()<<"Üres joystickadatok";
        msg("Üres joystickadatok",2);
    }
    else {
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

            QObject *object2 = ui->magmer->rootObject();
            object2->setProperty("alt", olvasott[12]*10);//magasság
            QObject *object3 = ui->compass->rootObject();
            object3->setProperty("fok", olvasott[26]);//iránytű adatai
        }
    }
//    if (joystickAdatok.size()>2){}


    if (ui->motegy->isChecked()==1){
        int val=ui->slid3->value();
        ui->slid1->setValue(val);
        ui->slid2->setValue(val);
    }
    //navigáció
    int bmot=ui->slid1->value();
    int jmot=ui->slid2->value();
    int navmota=ui->slid5->value();
    int navmotf=ui->slid4->value();
    if(joystickAdatok.size()>=14){
        if (joystickAdatok[4]==1){
            double elt=joystickAdatok[2]*200;
            bmot=int(bmot+elt);
            jmot=int(jmot-elt);
        }
        if (joystickAdatok[5]==1){
            motorNull();
            bmot=0;
            jmot=0;
        }
        if (joystickAdatok[11]==1){
            bmot=-200;
            jmot=200;
        }
        if (joystickAdatok[14]==1){
            bmot=200;
            jmot=-200;
        }

        if (joystickAdatok[3]==1){//középső gomb egyenesen haladjon
            bmot = jmot = (bmot + jmot)/2 ;
        }
        if (ui->dmotjoy->isChecked()==1){
            if(joystickAdatok[1]*1023>0){
                navmotf=int(joystickAdatok[1]*1023);
                navmota=0;
            }
            else{
                navmota=int(-joystickAdatok[1]*1023);
                navmotf=0;
            }
            ui->slid4->setValue(navmota);
            ui->slid5->setValue(navmotf);
        }

    }

    int sl;
    QString sliddat;
    sliddat = "Motor 1:\t"+ QString::number(bmot);
    sliddat = sliddat +"\nMotor 2:\t" + QString::number(jmot);
    sl = ui->slid3->value();
    sliddat = sliddat +"\nMotor közös:\t" + QString::number(sl);
    sliddat=sliddat+"\ncs1: " +QString::number(serDat[0])+"\ncs2: "+QString::number(serDat[1]);
    ui-> slidText->setText(sliddat);

    QList<double> idl;

    idl.append(0);//0 használatlan
    idl.append(jmot);//1 motor2 érték
    idl.append(0);//2 mélységmérés
    idl.append(0);//3 tápegység állapot
    idl.append(0);//4 ballaszttartály1 állapot
    idl.append(0);//5 ballaszttartály2 állapot
    idl.append(ui->slid6->value());//6 hűtőventillátor
    idl.append(0);//7 bal vezérsík - üres
    idl.append(0);//8 jobb vezérsík - üres
    idl.append(0);//9 motor reset kérés
    idl.append(bmot);//10 motor1 %
    idl.append(navmotf);//11 Navigációs motor felső
    idl.append(navmota);//12 Navigációs motor alsó
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
    msg("Parancssorba írt parancs: "+readedT,1);
    ui->cmd_p-> setText(ures);
    QString regiT = ui->command->toPlainText();
    ui->command-> setText(commands(readedT));
}

void GUI::openCmd()
{
    qDebug()<<"cmd megnyitása";
    msg("Parancssor megnyitása",1);
    ui->cmdDock->show();
    ui->cmdDock->activateWindow();
    ui->cmd_p->cursorWordForward(1);
}

void GUI::closeCmd()
{
    qDebug()<<"cmd bezárása";
    msg("Parancssor bezárása",1);
    ui->cmdDock->setHidden(1);
}

void GUI::motorNull()
{
    ui->slid1->setValue(0);
    ui->slid2->setValue(0);
    ui->motegy->setChecked(0);
}

void GUI::serkom()
{
    QByteArray data = mSerial->readLine();
    QString str = QString(data);
    QList<int> id=convInt(str);
    if(id != serDatElozo && id.size()>=19){
        serDat=id;
        serDatElozo=serDat;
        ui->serNyers->setText(str);
    }

    mSerial->clear(QSerialPort::AllDirections);
}

void GUI::serKeres()
{
    msg("Portok frissítése",1);
    mSerialPorts = QSerialPortInfo::availablePorts();

    ui->serKomBox->clear();
    ui->serKomBox->addItem("Nincs");
    for (QSerialPortInfo port : mSerialPorts) {
        ui->serKomBox->addItem(port.portName(), port.systemLocation());
    }
}

void GUI::serConn()
{
    ui->csatlSer->setEnabled(false);
    QString serialLoc  =  ui->serKomBox->currentData().toString();

    if (mSerial->isOpen()) {
        qDebug() << "Serial already connected, disconnecting!";
        msg("Soros kapcsolat már aktív, újracsatlakozás",2);
        mSerial->close();
    }

    mSerial->setPortName(serialLoc);
    mSerial->setBaudRate(QSerialPort::Baud115200);
    mSerial->setDataBits(QSerialPort::Data8);
    mSerial->setParity(QSerialPort::NoParity);
    mSerial->setStopBits(QSerialPort::OneStop);
    mSerial->setFlowControl(QSerialPort::NoFlowControl);

    if(mSerial->open(QIODevice::ReadWrite)) {
        qDebug() << "SERIAL: OK!";
        msg("Soros nyitás siekres",1);
    } else {
        qDebug() << "SERIAL: ERROR!";
        msg("Soros nyitás siekrtelen",3);
    }
    mSerial->clear(QSerialPort::AllDirections);

    ui->csatlSer->setEnabled(true);
}

void GUI::serDeconn()
{
    mSerial->close();
    msg("Soros lecsatlakozás",2);
}

QString GUI::commands(QString comm)
{
    QString alap="Parancs: "+comm+"\n";
    if (comm=="comm"){
        return alap+"Parancs végrehajtása siekeres";
    }

    else if(comm=="exit"){
        close();
        return alap+"Kilépés...";
    }

    else if(comm=="readUdp"){
//        read();
        return alap+"Nem hajtható végre, mert végtelen ciklus elindítását eredményezné";
    }

    else if(comm=="getJoy"){
        QString dat;
        for(int i=0; i<joystickAdatok.size(); i++)
        {
            dat += QString::number(joystickAdatok[i]);
            if(i<joystickAdatok.size()-1)
            dat += "," ;
        }
        return alap+"Joystick olvasott adatai:\n"+dat;
    }

    else if(comm=="PIDjoy"){
        QString dat;
        dat=QString::number(pr->processId());
        return alap+"Joystick továbbítás folyamat pID:\n"+dat;
    }

    else if(comm=="PIDkep"){
        QString dat;
        dat=QString::number(pr2->processId());
        return alap+"Kép továbbítás folyamat pID:\n"+dat;
    }

    else if(comm=="stopJoy"){
        QString dat;
        pr->kill();
        return alap+"Sikeres: "+dat;
    }

    else if(comm=="stopKep"){
        QString dat;
        pr2->kill();
        return alap+"Sikeres: "+dat;
    }
    else if(comm=="stop"){
        pr2->kill();
        pr->kill();
        return alap+"Minden alfolyamat leállítva ";
    }
    else if(comm=="h"){
        QString dat=comH;
        return alap+"Helptext:\n"+dat;
    }
    else if(comm=="startJoy"){
        return alap+stJ();
    }
    else if(comm=="startKep"){
        return alap+stK();
    }

    return "Nem található a kért parancs: "+comm;
}

QString GUI::stK()
{
    if(pr2->processId()==0)
    {
        //Kép adatokat mentő program indítása
        pr2 = new QProcess(this);
        pr2->start(pypath, QStringList() << keppath);
        if(pr2->processId()!=0){return "Kép folyamat\nSikeres indítás, új PID:\n"+QString::number(pr2->processId());}//sikeresség ellenőrzés
        else{return "Kép folyamat\nSikertelen indítás - program továbbra sem fut";}
    }
    else{
        return "Kép folyamat\nNincs szükség indításra, a folyamat már fut; PID:\n"+QString::number(pr2->processId());
    }
}

QString GUI::stJ()
{
    //Joystick adatokat mentő program idítása

    if(pr->processId()==0)
    {
        //Kép adatokat mentő program indítása
        pr = new QProcess(this);
        pr->start(pypath, QStringList() << joypath);
        if(pr->processId()!=0){return "Joystick folyamat\nSikeres indítás, új PID:\n"+QString::number(pr->processId());}//sikeresség ellenőrzés
        else{return "Joystick folyamat\nSikertelen indítás - program továbbra sem fut";}
    }
    else{
        return "Joystick folyamat\nNincs szükség indításra, a folyamat már fut; PID:\n"+QString::number(pr->processId());
    }
}


//Üzenőfelület - 1:message, 2:warning, 3:error
void GUI::msg(QString txt, int priority=1)
{
    QString message=ui->output->toPlainText();

    switch(priority){
    case 1:
        message=message+"MESSAGE - ";
        break;
    case 2:
        message=message+"WARNING - ";
        break;
    case 3:
        message=message+"ERROR - ";
        break;
    }

    message=message+txt+"\n";

    ui->output->setText(message);
    ui->output->moveCursor(QTextCursor::End);
    ui->output->setStyleSheet("body{font-size=12px;}");
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
QList<int> GUI::convInt(QString str){
    QTextStream stream(&str);
    QList<int> array;
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

    QFile file("../vezerlo-gui/program-datas/joystick.txt");

    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Error in file read";
        msg("Joystick fájl olvasásakor hiba",3);
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
}
QList<double> GUI::get_joystickAdatok()
{
    return joystickAdatok;
}


