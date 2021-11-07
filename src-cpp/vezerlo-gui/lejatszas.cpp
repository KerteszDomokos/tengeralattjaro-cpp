#include "lejatszas.h"
#include "ui_lejatszas.h"

#include <QFileDialog>
#include <QDebug>
#include <QIcon>
#include <QDomDocument>
#include <QTimer>

Lejatszas::Lejatszas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lejatszas)
{
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex(0);
    playing=0;

    timer = new QTimer(this);//időzítők
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Lejatszas::next_steps));
    ui->filenametxt->setText(fileName);
}

Lejatszas::~Lejatszas()
{
    closed();
    delete ui;
}

void Lejatszas::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Megnyitás"), fileName,tr("Aqualab fájlok (*.al, *.AL, *.*)"));

    ui->filenametxt->setText(fileName);

    msg("Lejátszásnál kiválasztott fájlnevet lekérheti a parancssorból",1);
}

void Lejatszas::startPlay()
{

    //The QDomDocument class represents an XML document.
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
       qDebug() << "Error while loading file";
    }
    // Set data into the QDomDocument before processing
    QString Errormsg;
    if(xmlBOM.setContent(&f,true,&Errormsg)){
        ui->fileervenyesseg_label->setText("Érvényes fájl, betölthető");
        ui->fileervenyesseg_label->setStyleSheet("QLabel{color:green;}");
    }else{
        ui->fileervenyesseg_label->setText("Érvénytelen fájl, betöltés siekretelen. Error: "+Errormsg);
        ui->fileervenyesseg_label->setStyleSheet("QLabel{color:red;}");
    }
    f.close();

     root=xmlBOM.documentElement();
     Component=root.firstChild().toElement();
    QString txt;


    // Get the first child of the component
     Child=Component.firstChild().toElement();
     tag = "Event";
     nodes = root.elementsByTagName(tag);
        ui->rekordszam->setText(QString::number(nodes.count()));
        ui->load->setMaximum(nodes.count());
        rekordszam=nodes.count();
        ui->idovonal->setMaximum(rekordszam);
        if(rekordszam>1200){
            ui->rekordfigy->setText("A rendszer max 1000 rekordot tölt be! Jelenlegi kezdőrekord: "+QString::number(0));
            ui->load->setMaximum(1200);
        }
        for(int i = 0; i < nodes.count() && i<1200; i++)
        {
            ui->load->setValue(i+1);
            QDomNode elm = nodes.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                ids.append(e.attribute("id").toLong());
                kuldendo.append(e.attribute("kuldendo"));
                olvasott.append(e.attribute("olvasott"));
                joystick.append(e.attribute("olvasott"));
                txt=txt+e.attribute("id")+" - "+e.attribute("kuldendo")+" - "+e.attribute("olvasott")+" - "+e.attribute("olvasott")+"\n";

            }
        }

        ui->xmladatok->setText(txt);

    play();
    connect(this,SIGNAL(xmlReload()),this,SLOT(getElements()));
}

void Lejatszas::lejatszas_idozito()
{
    if(playing==1){//Lejátszás
        ui->playgomb->setIcon(QIcon(":/icons/play"));
        playing=0;
        timer->stop();
    }else{
        ui->playgomb->setIcon(QIcon(":/icons/pause"));
        playing=1;
        timer->start(5);
        msg("Lejátszási időzítő indítása",1);
    }
}

void Lejatszas::getElements(long beg)
{
    QString txt;
    Child=Component.firstChild().toElement();
    tag = "Event";
    nodes = root.elementsByTagName(tag);
       ui->rekordszam->setText(QString::number(nodes.count()));
       ui->load->setMaximum(nodes.count());
       rekordszam=nodes.count();
       ui->idovonal->setMaximum(rekordszam);

       kuldendo.clear();
       ids.clear();
       olvasott.clear();
       joystick.clear();

       if(rekordszam>200){
           ui->rekordfigy->setText("A rendszer max 200 rekordot tölt be! Jelenlegi kezdőrekord: "+QString::number(beg));
           ui->load->setMaximum(200);
       }
       for(int i = beg; i < nodes.count() && i<beg+200; i++)
       {
           ui->load->setValue(i+1);
           QDomNode elm = nodes.at(i);
           if(elm.isElement())
           {
               QDomElement e = elm.toElement();
               ids.append(e.attribute("id").toLong());
               kuldendo.append(e.attribute("kuldendo"));
               olvasott.append(e.attribute("olvasott"));
               joystick.append(e.attribute("olvasott"));
               txt=txt+e.attribute("id")+" - "+e.attribute("kuldendo")+" - "+e.attribute("olvasott")+" - "+e.attribute("olvasott")+"\n";

           }
       }
       ui->xmladatok->setText(txt);

}

void Lejatszas::msg(QString t, int p)
{
    message(t,p);
}

void Lejatszas::updateNow()
{
    long id=0;
    if(ids.size()>1){
        id=long(ids[0]);
        nowID=ui->idovonal->value()-id;
        if(nowID+ids[0]<rekordszam){
            if(nowID<0){qDebug()<<"Now id kisebb mint nulla";nowID=0;}
            nowKuldendo=kuldendo[nowID];
            nowOlvasott=olvasott[nowID];
            nowJoystick=joystick[nowID];
       }else{
            if(playing==1){
                msg("Lejátszás vége",1);
                lejatszas_idozito();
            }
        }
    }
}

void Lejatszas::setDats(QString style)
{
    this->setStyleSheet(style);
}

void Lejatszas::slidMove()
{
    long pos=ui->idovonal->value();
    if (pos-lastLoad>90 || pos-lastLoad<-90){
        if(pos<=90){getElements(0);}else{getElements(pos-90);}
        lastLoad=pos;
        qDebug()<<"Új null ID: "<<ids[0];
    }
}

void Lejatszas::next_steps()
{
    ui->idovonal->setValue(ui->idovonal->value()+1);
}

QString Lejatszas::getFileName() const
{
    return fileName;
}

void Lejatszas::setFileName(const QString &value)
{
    fileName = value;
}

void Lejatszas::valaszt()
{
    ui->filenametxt->setText(fileName);
}

QString Lejatszas::getNowJoystick() const
{
    return nowJoystick;
}

QString Lejatszas::getNowOlvasott() const
{
    return nowOlvasott;
}

QString Lejatszas::getNowKuldendo() const
{
    return nowKuldendo;
}

long Lejatszas::getNowID() const
{
    return nowID;
}

long Lejatszas::getRekordszam() const
{
    return rekordszam;
}

bool Lejatszas::getGuiUpdate() const
{
    return guiUpdate;
}

bool Lejatszas::getJoy() const
{
    return joy;
}

bool Lejatszas::getOlv() const
{
    return olv;
}

bool Lejatszas::getKuld() const
{
    return kuld;
}
