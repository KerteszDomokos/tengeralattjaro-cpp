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

    QDomElement root=xmlBOM.documentElement();
    QDomElement Component=root.firstChild().toElement();
    QString txt;

    QList<long> ids;
    QList<QString> kuldendo;
    QList<QString> olvasott;
    QList<QString> joystick;

    // Get the first child of the component
    QDomElement Child=Component.firstChild().toElement();
    QString tag = "Event";
    QDomNodeList nodes = root.elementsByTagName(tag);
        ui->rekordszam->setText(QString::number(nodes.count()));
        ui->load->setMaximum(nodes.count());
        for(int i = 0; i < nodes.count(); i++)
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
