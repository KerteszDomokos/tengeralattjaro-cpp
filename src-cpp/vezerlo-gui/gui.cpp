#include "gui.h"
#include "ui_gui.h"

#include "felvetel.h"
#include "lejatszas.h"

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
#include <QProcess>
#include <QIODevice>
#include <QStringList>
#include <thread>
#include <mutex>
#include "sockread.h"
#include <cmath>
#include <QTextCursor>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>
#include <QImage>
#include <QElapsedTimer>
#include <QtXml>
#include <QTextStream>
#include <QDomElement>
#include <QDomDocument>
#include <QDialog>
#include <QDate>
#include <QDir>

SockRead sock;


QString bejovo="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
std::mutex bejovo_mutex;

QList<double> kuldendo={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
std::mutex kuldendo_mutex;


void read(){
    QString dat;
    QString elozoOlv;
    QList<double> sending; QString sendingS;
    long rsz=0;
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


    ui->horizont->setSource(QUrl(QStringLiteral("qrc:/qml-files/horizon")));
    ui->joyh->setSource(QUrl(QStringLiteral("qrc:/qml-files/joy")));
    ui->magmer->setSource(QUrl(QStringLiteral("qrc:/qml-files/melyseg")));
    ui->compass->setSource(QUrl(QStringLiteral("qrc:/qml-files/compass")));
    ui->radarG->setSource(QUrl(QStringLiteral("qrc:/qml-files/radar")));
    ui->robotkarG->setSource(QUrl(QStringLiteral("qrc:/qml-files/robotkar")));


    QPixmap pm = QPixmap("G:/Privát adatok/.Programozás/Projektek/Tengeralattjáró/v1 - Github/tengeralattjaro-cpp/src-cpp/vezerlo-gui/program-datas/live.jpg"); // <- path to image file
    ui->ad->setPixmap(pm);
    ui->ad->setScaledContents(false);


    QTimer *timer = new QTimer(this);//időzítők
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&GUI::update));
    timer->start(20);

    QTimer *kt = new QTimer(this);
    connect(kt, &QTimer::timeout, this, QOverload<>::of(&GUI::fps));
    kt->start(50);

    QTimer *friss = new QTimer(this);
    connect(friss, &QTimer::timeout, this, QOverload<>::of(&GUI::updateKommData));
    friss->start(2);


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

    ui->cmdDock->setHidden(1);

    mSerial = new QSerialPort(this);

    connect(mSerial, &QSerialPort::readyRead,
            this, &GUI::serkom);

    ballaszt_manualis_click();

    qDebug()<<QDate::currentDate().QDate::toString("yy-M-d");
}

GUI::~GUI()
{
    mSerial->close();
    delete ui;
    pr->kill();//joystick folyamat befejezése
    pr2->kill();//kép folyamat befejezése

    if(mentes_onoff==1){
        mentes_onoff=0;
        mentid=0;
        xmlFile=new QFile ("../mentett.xml");
        if (!xmlFile->open(QFile::WriteOnly | QFile::Text ))
           {
               msg("Sikertelen fájl nyitás",2);
               qDebug()<<"Hibás fájlnyitás";
               xmlFile->close();
           }
        else{
            xmlContent= new QTextStream(xmlFile);
            QTextStream stream(xmlFile);
            stream << ment_doc->toString();
        }

    }

}


void GUI::fps()
{
    QPixmap pm2 = QPixmap("G:/Privát adatok/.Programozás/Projektek/Tengeralattjáró/v1 - Github/tengeralattjaro-cpp/src-cpp/vezerlo-gui/program-datas/live.jpg"); // <- path to image file
    if (pm2.isNull()!=1){//ha a kép létezik:
        QImage img = pm2.toImage();//érvényes kép
            if(  img.pixel(img.width()-1,img.height()-1 )  ==  4286611584   &&  img.pixel(img.width()/2,img.height()-1 )  ==  4286611584  &&  img.pixel(0,img.height()-1 )  ==  4286611584  )
            {
                int hatar=5;
                kepHiba++;
                if(kepHiba>=hatar){
                    msg("Kép egymás után "+QString::number(hatar)+"-szer hibás",3);
                }
            }
            else{
                kepHiba=0;
                ui->ad->setPixmap(pm2);
                ui->ad->setScaledContents(false);
            }
        }
    else{
       // if(sz<5){goto ujraproba;}
        msg("Kép betöltés sikertelen",2);
    }
    //Külső folyamatok sikerességére vonatkozó adatok
    int pid=pr->processId();
    ui->joyPID->setText(QString::number(pid));
    if (pid==0){ui->joyPID->setStyleSheet("QLineEdit {background-color: red;}");ui->startJoyb->setEnabled(true);}
    else{ui->joyPID->setStyleSheet("QLineEdit {background-color: green;}");ui->startJoyb->setEnabled(false);}
    pid=pr2->processId();
    ui->kepPID->setText(QString::number(pid));
    if (pid==0){ui->kepPID->setStyleSheet("QLineEdit {background-color: red;}");ui->startKepb->setEnabled(true);}
    else{ui->kepPID->setStyleSheet("QLineEdit {background-color: green;}");ui->startKepb->setEnabled(false);}


    ui->ballaszt_balval->setText(QString::number(ui->ballaszt_baltart->value()));
    ui->ballaszt_jobbval->setText(QString::number(ui->ballaszt_jobbtart->value()));

}



void GUI::update()
{

    QList<double> jd=get_joystickAdatok();
    olvasott=conv(bejovoFriss);

    if(jd.isEmpty()==1){
        msg("Üres joystickadatok",2);
    }
    else {
    if(ui->joyon->isChecked()==1){
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


    double dx=0;
    double dy=0;


    if (olvasott.size()>28){
        if(olvasott[22+4]>0){dx=std::sqrt(pow(olvasott[22+4]-90,2));}else{dx=-(olvasott[22+4]+90);}
        if(olvasott[23+4]>0){dy=std::sqrt(pow(olvasott[23+4]-90,2));}else{dy=-(olvasott[23+4]+90);}
        QObject *object = ui->horizont->rootObject();
        object->setProperty("pitchAngle", -dx);//dőlés
        object->setProperty("rollAngle", -dy);//forgás

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
        if(olvasott.size()>28){
QTableWidgetItem *i;
QColor red(QColor("red"));
QColor green(QColor("green"));
ui->foadatok_1->setItem(0,0, i = new QTableWidgetItem(QString::number(0)));//sebesség
    if(0 > 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_1->setItem(0,1, i = new QTableWidgetItem(QString::number(dx)));//dőlés x
    if(dx > 30 || dx < -30){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_1->setItem(0,2, i = new QTableWidgetItem(QString::number(dy)));//dőlés y
    if(dy > 30|| dy < -30){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_1->setItem(0,3, i = new QTableWidgetItem(QString::number(olvasott[9])));//motorB
    if(0 > 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_1->setItem(0,4, i = new QTableWidgetItem(QString::number(olvasott[10])));//motorJ
    if(0 > 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_1->setItem(0,5, i = new QTableWidgetItem(QString::number(olvasott[26+4])));//test iránya
ui->foadatok_2->setItem(0,0, i = new QTableWidgetItem(QString::number(0)));//döntőmotor felső
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_2->setItem(0,1, i = new QTableWidgetItem(QString::number(0)));//alsó
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_2->setItem(0,2, i = new QTableWidgetItem(QString::number(0)));//vízhőm
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_2->setItem(0,3, i = new QTableWidgetItem(QString::number(0)));//wifi jelerősség
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_2->setItem(0,4, i = new QTableWidgetItem(QString::number(olvasott[12])));//nyomás
    if(olvasott[12] > 10){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_2->setItem(0,5, i = new QTableWidgetItem(QString::number(olvasott[0])));//sikerese a komm
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_3->setItem(0,0, i = new QTableWidgetItem(QString::number(olvasott[5])));//belső hőm
    if(olvasott[5]> 30){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_3->setItem(0,1, i = new QTableWidgetItem(QString::number(olvasott[7])));//DHT hőm
    if(olvasott[7]> 30){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_3->setItem(0,2, i = new QTableWidgetItem(QString::number(olvasott[8])));//páratart
    if(olvasott[8]> 70){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_3->setItem(0,3, i = new QTableWidgetItem(QString::number(olvasott[1])));//belső víz
    if(olvasott[1]> 20){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_3->setItem(0,4, i = new QTableWidgetItem(QString::number(olvasott[21+4])));//rpi proc
    if(olvasott[21]> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_3->setItem(0,5, i = new QTableWidgetItem(QString::number(olvasott[20+4])));// serbuff fedélzet
    if(olvasott[20]> 1000){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_4->setItem(0,0, i = new QTableWidgetItem(QString::number(olvasott[11])));//5vakk1 raspi akku
    if(olvasott[11]< 950){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_4->setItem(0,1, i = new QTableWidgetItem(QString::number(olvasott[13])));//12vakku1 motor
    if(olvasott[13]< 950){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_4->setItem(0,2, i = new QTableWidgetItem(QString::number(0)));//5v masodlagos
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_4->setItem(0,3, i = new QTableWidgetItem(QString::number(0)));//12v masodlagos
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_4->setItem(0,4, i = new QTableWidgetItem(QString::number(olvasott[4])));//csp1
    if(olvasott[4]< 950){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
ui->foadatok_4->setItem(0,5, i = new QTableWidgetItem(QString::number(0)));//csp2
    if(0> 65){i->setData(Qt::BackgroundRole,red);} else{i->setData(Qt::BackgroundRole,green);}
            QObject *object2 = ui->magmer->rootObject();
            object2->setProperty("alt", olvasott[12]);//magasság
            QObject *object3 = ui->compass->rootObject();
            object3->setProperty("fok", olvasott[26+3]);//iránytű adatai

            QString radaradat="Szög: "+QString::number(olvasott[12]*5+45)+"\n"+
                              "-4: "+QString::number(olvasott[13])+"\n"+
                              "-3: "+QString::number(olvasott[14])+"\n"+
                              "-2: "+QString::number(olvasott[15])+"\n"+
                              "-1: "+QString::number(olvasott[16])+"\n"+
                              "Friss: "+QString::number(olvasott[17]);
            ui->radar->setText(radaradat);

            ui->ballaszt_jobbnyom_real->setText(QString::number(olvasott[19]));
            ui->ballaszt_balnyom_real->setText(QString::number(olvasott[18]));

        if(ui->radaron->isChecked()==1){

            QObject *object = ui->radarG->rootObject();

            for (int i=0; i<5; i++){
             int fid = olvasott[12]-5+i;
             if(fid<=0){
                 fid=18+fid;
             }

             int fok=(olvasott[12]-i)*5+45;
             int tav=std::cos(rad(fok-90))*olvasott[13+i];
             int x=std::sin(rad(fok-90))*olvasott[13+i];
             x=200+(x*2);

            QObject *rect = object->findChild<QObject*>("p"+QString::number(fid));

                if (rect){
                    rect->setProperty("x", QString::number(x));
                    rect->setProperty("y", QString::number(300-(tav*2)));
                }
                else{
                    msg("Qml radar adatbellítás sikertelen (!rect)",2);
                }
            }

          }
        if (ui->robotkarqmlon->isChecked()==1){
        QObject *object = ui->robotkarG->rootObject();
        QList<QString> pots={"alapV","forgV","pot2V","pot3V"};//robotkar potméterek
        if (object){
            QString txt="Robotkar adatok:\n";
            for (int i; i<3; i++){
                txt=txt+"Pot"+QString::number(i+1)+": ";
                QVariant a=QQmlProperty(object, pots[i]).read();
                txt=txt+QString::number(a.toInt())+"\n";


            ui->robotkaradatok->setText(txt);


            }
        }
      }
   }
}
//    if (joystickAdatok.size()>2){}


    if (ui->motegy->isChecked()==1){
        int val=ui->slid3->value();
        ui->slid1->setValue(val);
        ui->slid2->setValue(val);
    }
    //navigáció
    int bmot;
    int jmot;
    if(ui->serplot->isChecked()==0){
        bmot=ui->slid1->value();
        jmot=ui->slid2->value();
    }
    else{
        bmot=serDat[0];
        jmot=serDat[1];
        ui->motegy->setChecked(0);
    }
    int navmota=ui->slid5->value();
    int navmotf=ui->slid4->value();

    if(joystickAdatok.size()>=14){
        if(joystickAdatok[7]==1){
            ui->serplot->setChecked(1);
        }
        if(joystickAdatok[10]==1){
            ui->motegy->setChecked(1);
        }
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
        if(joystickAdatok[6]==1){
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
            ui->slid4->setValue(navmotf);
            ui->slid5->setValue(navmota);
        }

    }
    if(ui->serplot->isChecked()==1){
        ui->slid1->setValue(bmot);
        ui->slid2->setValue(jmot);
    }

    int sl;
    QString sliddat;
    sliddat = "Motor 1:\t"+ QString::number(bmot);
    sliddat = sliddat +"\nMotor 2:\t" + QString::number(jmot);
    sl = ui->slid3->value();
    sliddat = sliddat +"\nMotor közös:\t" + QString::number(sl);
    sliddat=sliddat+"\ncs1: " +QString::number(serDat[0])+"\ncs2: "+QString::number(serDat[1]);
    ui-> slidText->setText(sliddat);

    if(ui->fordtest->isChecked()==1){
        int a=bmot;
        int b=jmot;
        bmot=b;
        jmot=a;
    }

    int szoros=ui->ballasztErz->value();
    QList<double> idl;

    idl.append(0);//0 használatlan
    idl.append(jmot);//1 motor2 érték
    idl.append(0);//2 mélységmérés
    idl.append(0);//3 tápegység állapot
    idl.append(0);//4 ballaszttartály1 állapot
    idl.append(0);//5 ballaszttartály2 állapot
    idl.append(ui->hutes->value());//6 hűtőventillátor
    idl.append(0);//7 bal vezérsík - üres
    idl.append(0);//8 jobb vezérsík - üres
    idl.append(0);//9 motor reset kérés
    idl.append(bmot);//10 motor1 %
    idl.append(ui->pontonkormany->value());//11 Pontonhajó kormány
    idl.append(ui->radaron->isChecked());//12 radar kibe
    idl.append(ui->talcaHajtas->value());//13 tálca hajtásszög
    idl.append(0);//14 Küldés időpontja
    idl.append(0);//15 robotkar adatok ...
    idl.append(navmotf);//16 Navigációs motor felső
    idl.append(navmota);//17 Navigációs motor alsó
    idl.append(ui->kameraon->isChecked());//18 élő kép kérés
    idl.append(0);//19 Pontonhajó motor
    idl.append(ui->ballaszt_baltart->value()*10/szoros);//20 ballaszt bal tartály százalék
    idl.append(ui->ballaszt_jobbtart->value()*10/szoros);//21 ballaszt jobb tartaly százalék
    idl.append(60);//22 SSH reset kérés
    idl.append(ui->talcaAktiv->isChecked());//23 Tálca érték állítható
    idl.append(0);//24 robotkar adatok ...
    idl.append(0);//25 robotkar adatok ...
    idl.append(0);//26 robotkar adatok ...
    idl.append(0);//27 robotkar adatok ...
    idl.append(0);//28 robotkar adatok ...
    idl.append(0);//29 robotkar adatok ...
    idl.append(0);//30 robotkar adatok ...
    idl.append(0);//31 robotkar adatok ...

    //qDebug()<<idl;


    kuldendoFriss=idl;

    QString string;
    for(int i=0; i<idl.size(); i++)
    {
        string += QString::number(idl[i]);
        if(i<idl.size()-1)
        string += "," ;
    }
    ui->nyersIrando->setText(string);

    if (mentes_onoff==1){
        QDomElement l = ment_doc->createElement("Event");
        l.setAttribute("id",QString::number(mentid));

        l.setAttribute("joystick",listToStr(joystickAdatok));
        l.setAttribute("olvasott",listToStr(olvasott));
        l.setAttribute("kuldendo",listToStr(idl));

        root_xml->appendChild(l);
        mentid++;

    }

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
    ui->serplot->setChecked(0);
}

void GUI::updateKommData()
{
    bejovo_mutex.lock();
    bejovoFriss=bejovo;
    bejovo_mutex.unlock();

    kuldendo_mutex.lock();
    kuldendo=kuldendoFriss;
    kuldendo_mutex.unlock();

}

double GUI::rad(double degree)
{
    double pi = 3.14159265359;
    return (degree * (pi / 180));
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

void GUI::ponton_stop()
{
    ui->pontonmotor->setValue(0);
}

void GUI::ponton_egyenes()
{
    ui->pontonkormany->setValue(0);
}

//Ha bekapcsoltam a sporolast akkor kikapcsol. Ezt csak egyszer hajtja végre tehát fölülírható! A loopban egy hasonló if a felülírhatatlan döntéseket kezeli.
void GUI::akksporolas()
{
    if(ui->sporolas->isChecked()==1){
        //felülírható:
        ui->radaron->setChecked(0);
        //felülírhatatlan:
        ui->kameraon->setChecked(0); ui->kameraon->setEnabled(0);

        msg("Spórolás bekapcsolva!",1);
    }
    else{
        ui->kameraon->setEnabled(1);
        msg("Spórolás kikapcsolva",1);
    }
}

void GUI::ballaszt_manualis_click()
{
    if(ui->ballaszt_manualis->isChecked()==1){
        ui->ballaszt_lebeges->setChecked(0);
        ui->ballaszt_lassuemelk->setChecked(0);
        ui->ballaszt_lassully->setChecked(0);
        ui->ballaszt_lebeges->setEnabled(0);
        ui->ballaszt_lassuemelk->setEnabled(0);
        ui->ballaszt_lassully->setEnabled(0);

        ui->ballaszt_baltart->setEnabled(1);
        ui->ballaszt_jobbtart->setEnabled(1);
    }
    else{
        ui->ballaszt_lebeges->setEnabled(1);
        ui->ballaszt_lassuemelk->setEnabled(1);
        ui->ballaszt_lassully->setEnabled(1);

        ui->ballaszt_baltart->setEnabled(0);
        ui->ballaszt_jobbtart->setEnabled(0);
    }
}

void GUI::ballaszt_emelkedes()
{

}

void GUI::ballaszt_erzekenyseg()
{
    int erz=ui->ballasztErz->value();
    int val=ui->ballaszt_baltart->maximum()/10;
    int val2=ui->ballaszt_jobbtart->maximum()/10;
    int valeb=ui->ballaszt_baltart->value();
    int valej=ui->ballaszt_jobbtart->value();

    ui->ballaszt_jobbtart->setMaximum(10*erz);
    ui->ballaszt_baltart->setMaximum(10*erz);
    ui->ballaszt_baltart->setValue(erz*(valeb/val));
    ui->ballaszt_jobbtart->setValue(erz*(valej/val2));



}

void GUI::talca_kinyit()
{
    ui->talcaHajtas->setValue(ui->talcaHajtas->maximum());
}

void GUI::talca_becsuk()
{
    ui->talcaHajtas->setValue(ui->talcaHajtas->minimum());
}

void GUI::ballasztBalmin()
{
    //ballaszt_baltart
    ui->ballaszt_baltart->setValue(0);
}

void GUI::ballasztBalmax()
{
    ui->ballaszt_baltart->setValue(ui->ballaszt_baltart->maximum());
}

void GUI::ballasztBalk()
{
    ui->ballaszt_baltart->setValue(ui->ballaszt_baltart->maximum()/2);
}

void GUI::ballasztJobbk()
{
    ui->ballaszt_jobbtart->setValue(ui->ballaszt_jobbtart->maximum()/2);
}

void GUI::ballasztJobbmin()
{
    ui->ballaszt_jobbtart->setValue(0);
}

void GUI::ballasztJobbmax()
{
    ui->ballaszt_jobbtart->setValue(ui->ballaszt_jobbtart->maximum());
}

void GUI::set_darkmode()
{
    QFile styleFile( ":/programs/resources/dark-style.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    styleFile.close();

    QString st="QWidget{background: black;color:rgb(0, 255, 0);}";
    ui->centralwidget->setStyleSheet(style);
    ui->darkmode->setChecked(1);
    ui->lightmode->setChecked(0);
}

void GUI::set_lightmode()
{
    QString st="QWidget{background: black;color:rgb(0, 255, 0);}";
    ui->centralwidget->setStyleSheet("");
    ui->darkmode->setChecked(0);
    ui->lightmode->setChecked(1);
}

void GUI::mentes()
{

    if(ui->rogzites_check->isChecked()==1){
        msg("Mentés kezdése",1);
        ment_doc=new QDomDocument;
        //make the root element
        root_xml = new QDomElement(ment_doc->createElement("Merules"));
        ment_doc->appendChild(*root_xml);
        mentes_onoff=1;

    }else{
        msg("Mentés befejezése",1);
        mentes_onoff=0;
        mentid=0;
        int runID=0;


        QList<QString> fn;
        QDir d(felvPathGyok);
        QStringList files=d.entryList(QStringList()<<"*.al"<<"*.AL",QDir::Files);
        foreach(QString filename, files) {
            fn.append(filename);
            }

        for (int i=0; i<fn.length();i++){
            QString del = fn[i].replace(0,16,"").replace(2,3,"");
            if(del==felvPath){
                fn.append(generatePath(i+1));
                msg("Fájl felülírás kikerülése. Új útvonal: "+generatePath(i+1),2);
            }
            for (int da=0; da<100;da++){
                QString c;
                if(da<10){c="0";}
                c=c+QString::number(da);
                if(del==c){
                    runID=da+1;
                }
            }
            felvPath=generatePath(runID);
        }
        msg("Fájl felülírás kikerülése. Új útvonal: "+generatePath(runID),2);   //Biztonsági funkció, fájl fölülírás nincsen


        xmlFile=new QFile (felvPath);
        if (!xmlFile->open(QFile::WriteOnly | QFile::Text ))
           {
               msg("Sikertelen fájl nyitás"+felvPath,2);
               xmlFile->close();
           }
        else{
            xmlContent= new QTextStream(xmlFile);
            QTextStream stream(xmlFile);
            stream << ment_doc->toString();
        }

    }
}

void GUI::mentesDialog()
{
    widget = new Felvetel;
    widget->open();
    connect(widget,SIGNAL(accepted()),this,SLOT(felvAccept()));
}

void GUI::felvAccept()
{
    joyIN = widget->getJoyIN();
    konzIN = widget->getKonzIN();
    olvIN = widget->getOlvIN();
    kuldIN = widget->getKuldIN();
    defPathIN = widget->getDefPathIN();
    kepIN = widget->getKepIN();
    felvPath = widget->getFullPath();
    felvPathGyok=widget->getFileName();
    delete widget;
}

void GUI::lejatszasOpen()
{
    lejatszas=new Lejatszas;
    lejatszas->show();
    connect(lejatszas,SIGNAL(play()),this,SLOT(goPlay()));

}

void GUI::goPlay()
{
    playing=1;
    kuld_play=lejatszas->getKuld();
    olv_play=lejatszas->getOlv();
    joydat_play=lejatszas->getJoy();
    guiupdate_play=lejatszas->getGuiUpdate();
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

    QFile file("G:/Privát adatok/.Programozás/Projektek/Tengeralattjáró/v1 - Github/tengeralattjaro-cpp/src-cpp/vezerlo-gui/program-datas/joystick.txt");

    if (!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Error in file read";
        msg("Joystick fájl olvasásakor hiba",3);
//        QMessageBox::information(0, "Error", file.errorString());
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

void GUI::ment()
{

}

QString GUI::listToStr(QList<double> l)
{
    QString string;
    elozoOlvasottList=olvasott;
    for(int i=0; i<l.size(); i++)
    {
        string += QString::number(l[i]);
        if(i<l.size()-1)
        string += " " ;
    }
    return string;
}

QString GUI::listToStr(QList<int> l)
{
    QString string;
    elozoOlvasottList=olvasott;
    for(int i=0; i<l.size(); i++)
    {
        string += QString::number(l[i]);
        if(i<l.size()-1)
        string += " " ;
    }
    return string;
}

QString GUI::generatePath(int id)
{
    QString p=QDate::currentDate().QDate::toString("yy-MM-dd");
    QString nam="/merules"+p+"-";
    if(id<10){nam=nam+"0";}
    nam=nam+QString::number(id)+".al";
    QString fullPath=felvPathGyok+nam;
    return fullPath;
}



