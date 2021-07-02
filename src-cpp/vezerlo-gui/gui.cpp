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





GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    QPixmap pm("G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\Tengeralattjaro-RUV\\src-py\\camToSave.jpg"); // <- path to image file
    ui->horizont->setSource(QUrl::fromLocalFile("../vezerlo-gui/horizon.qml"));
    QObject *object = ui->horizont->rootObject();
    object->setProperty("rollAngle", 10);
    object->setProperty("pitchAngle", 10);
    ui->hd->setSource(QUrl::fromLocalFile("../vezerlo-gui/3dview.qml"));
    ui->hd->show();

    ui->ad->setPixmap(pm);
    ui->ad->setScaledContents(false);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::update));
    timer->start(100);


}

GUI::~GUI()
{
    delete ui;
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
    qDebug()<<joydat();
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

    QFile file("G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\Tengeralattjaro-RUV\\src-cpp\\vezerlo-gui\\joystick.txt");

    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Error in file read";
        QMessageBox::information(0, "error", file.errorString());
        return;
        }
    QString str;
    QTextStream in(&file);
    str = in.readLine();
    QTextStream stream(&str);
    while (!stream.atEnd()) {
        double number;
        stream >> number;
        array.append(number);
    }
    joystickAdatok=array;
    return;
}

QList<double> GUI::get_joystickAdatok()
{
    return joystickAdatok;
}


