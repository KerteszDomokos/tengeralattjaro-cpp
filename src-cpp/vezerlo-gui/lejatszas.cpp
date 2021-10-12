#include "lejatszas.h"
#include "ui_lejatszas.h"

#include <QFileDialog>
#include <QDebug>
#include <QIcon>
#include <QDomDocument>

Lejatszas::Lejatszas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lejatszas)
{
    ui->setupUi(this);
    ui->toolBox->setCurrentIndex(0);
}

Lejatszas::~Lejatszas()
{
    delete ui;
}

void Lejatszas::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Megnyitás"), fileName,tr("Aqualab fájlok (*.al, *.AL, *.*)"));

    ui->filenametxt->setText(fileName);
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
        ui->toolBox->setCurrentIndex(1);


    play();
    connect(this,SIGNAL(xmlReload()),this,SLOT(getElements()));
}

void Lejatszas::lejatszas_idozito()
{
    if(playing==1){//Lejátszás
        ui->playgomb->setIcon(QIcon(":/icons/play"));
        playing=0;
    }else{
        ui->playgomb->setIcon(QIcon(":/icons/pause"));
        playing=1;
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

void Lejatszas::updateNow()
{
    nowID=ui->idovonal->value()-lastLoad;
    if(nowID<0){qDebug()<<"Now id kisebb mint nulla";}else{
    nowKuldendo=kuldendo[nowID];
    nowOlvasott=olvasott[nowID];
    nowJoystick=joystick[nowID];
    }
}

void Lejatszas::slidMove()
{
    long pos=ui->idovonal->value();
    if (pos-lastLoad>100 || pos-lastLoad<-100){
        if(pos<=100){getElements(0);}else{getElements(pos-100);}
        lastLoad=pos;
        qDebug()<<"Trig"<<ids[0];
    }
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
