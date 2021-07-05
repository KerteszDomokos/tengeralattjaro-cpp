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
#include "sockread.h"




SockRead sock;

QString bejovo="";
std::mutex bejovo_mutex;

void read(){
    QString dat;
    QString elozoOlv;
    while(true){
        dat=sock.readS();
        Sleep(1);
        if (dat==""){
            Sleep(10);
        }
        else{
//          qDebug()<<dat;
            if(dat!=elozoOlv){
                bejovo_mutex.lock();
                bejovo=dat;
                bejovo_mutex.unlock();
                elozoOlv=bejovo;
            }
        }
    }

}

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    QPixmap pm("G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\Tengeralattjaro-RUV\\src-py\\camToSave.jpg"); // <- path to image file
    ui->horizont->setSource(QUrl::fromLocalFile("..\\vezerlo-gui\\horizon.qml"));
    QObject *object = ui->horizont->rootObject();
    object->setProperty("rollAngle", 10);
    object->setProperty("pitchAngle", 10);
    ui->hd->setSource(QUrl::fromLocalFile("../vezerlo-gui/3dview.qml"));
    ui->hd->show();

    ui->joyh->setSource(QUrl::fromLocalFile("..\\vezerlo-gui\\joy.qml"));
    //QObject *object = ui->horizont->rootObject();


    ui->ad->setPixmap(pm);
    ui->ad->setScaledContents(false);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::update));
    timer->start(5);

    //Joystick adatokat mentő program idítása

    QString file = "G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\joystick.py";
    pr->start("C:/Users/Gábor/AppData/Local/Programs/Python/Python38-32/python.exe", QStringList() << file);

    std::thread ob(read);
    ob.detach();


}

GUI::~GUI()
{
    delete ui;
    pr->terminate();//joystick folyamat befejezése
}

void GUI::update()
{
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
bejovo_mutex.lock();
    if(bejovo!=elozoOlv){
        elozoOlv=bejovo;
        ui->nyersOlvasott->setText(bejovo);
    }
bejovo_mutex.unlock();

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
    QString wrt="ElőreHátra:\n"+QString::number(joystickAdatok[0])+"\nJobbraBalra:\n"+QString::number(joystickAdatok[1])+"\nForgat:\n"+QString::number(joystickAdatok[2]);
    ui->joySzogadatok->setText(wrt);
}
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


