#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <QDebug>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    otherThema();
    ui->qssszabvany->setOpenExternalLinks(1);
}

settings::~settings()
{
    delete ui;
}

void settings::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Megnyitás"), fileName,tr("Aqualab fájlok (*.qss, *.QSS)"));

    ui->filename_tema->setText(fileName);

    msg(tr("Lejátszásnál kiválasztott fájlnevet lekérheti a parancssorból"),1);
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QString ss = QString(file.readAll());
    file.close();
    ui->temateszt->setStyleSheet(ss);
}

void settings::otherThema()
{
    if(ui->masiktema->isChecked()==1){
        ui->filename_tema->setEnabled(1);
        ui->filevalasztas->setEnabled(1);
        ui->qssszabvany->setEnabled(1);
        ui->temavalaszto->setEnabled(0);
        ui->deftema_label->setEnabled(0);
    }
    else{
        ui->filename_tema->setEnabled(0);
        ui->filevalasztas->setEnabled(0);
        ui->qssszabvany->setEnabled(0);
        ui->temavalaszto->setEnabled(1);
        ui->deftema_label->setEnabled(1);
    }
}

void settings::modvalasztas(QString mod)
{
    QString ss;
    if(mod=="Világos mód"|| mod=="Light mode"){
        ss="";
    }
    else if(mod=="Sötét mód" || mod=="Dark mode"){
        QFile file(":/programs/darkmode");
        file.open(QFile::ReadOnly);
        ss = QString(file.readAll());
        file.close();
    }

    ui->temateszt->setStyleSheet(ss);
    chstyle=ss;
}

void settings::beavleh()
{
    qDebug()<<"Act";
}

void settings::beav_reset()
{
    ui->ballasztereszt->setChecked(0);
    ui->pontonhajoelerh->setChecked(1);
    ui->robotkaeng->setChecked(1);
    ui->parancssor->setChecked(1);
    ui->manbal->setChecked(1);
}

void settings::hatfoly()
{

}

void settings::updatetime_reset()
{
    ui->updatetime->setValue(20);
}



QString settings::getChstyle() const
{
    return chstyle;
}

