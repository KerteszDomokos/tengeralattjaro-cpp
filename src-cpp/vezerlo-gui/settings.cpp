#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <QDebug>
#include <QSettings>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    otherThema();
    beavleh();
    hatfoly();
    ui->qssszabvany->setOpenExternalLinks(1);
    sets=new QSettings("Aqualab vezérlő", "AquaLab");
    getUserdat();
    applyuserdat();
}

settings::~settings()
{
    qDebug()<<"Settings deleted";
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
void settings::getUserdat()
{
    QVariant val;
    beavdatas=sets->value("beavleh").value<QList<bool>>();
    this->setStyleSheet(sets->value("Tema").toString());
    uptime=sets->value("updateTime").toInt();
}

void settings::applyuserdat()
{
    ui->temavalaszto->setCurrentText(sets->value("modename").toString());
    modvalasztas(sets->value("modename").toString());
    if (beavdatas.length()>=8){
        ui->ballasztereszt->setChecked(beavdatas[0]);
        ui->manbal->setChecked(beavdatas[1]);
        ui->parancssor->setChecked(beavdatas[2]);
        ui->update->setChecked(beavdatas[3]);
        ui->joystickpr->setChecked(beavdatas[4]);
        ui->kepudp->setChecked(beavdatas[5]);
        ui->kommthread->setChecked(beavdatas[6]);
        ui->pontonhajoelerh->setChecked(beavdatas[7]);
        ui->robotkaeng->setChecked(beavdatas[8]);
    }
 ui->updatetime->setValue(uptime);
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
        modename="Világos mód";
    }
    else if(mod=="Sötét mód" || mod=="Dark mode"){
        QFile file(":/programs/darkmode");
        file.open(QFile::ReadOnly);
        ss = QString(file.readAll());
        file.close();
        modename="Sötét mód";
    }

    ui->temateszt->setStyleSheet(ss);
    chstyle=ss;
}


void settings::beavleh()
{
    balman=ui->manbal->isChecked();
    balereszt=ui->ballasztereszt->isChecked();
    robotkarena=ui->robotkaeng->isChecked();
    cmdav=ui->parancssor->isChecked();
    pontonav=ui->pontonhajoelerh->isChecked();
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
    frissonoff=ui->update->isChecked();
    uptime=ui->updatetime->value();
    joyena=ui->joystickpr->isChecked();
    komena=ui->kommthread->isChecked();
    kepena=ui->kepudp->isChecked();
}

void settings::updatetime_reset()
{
    ui->updatetime->setValue(20);
}

int settings::getUptime() const
{
    return uptime;
}

bool settings::getKomena() const
{
    return komena;
}

bool settings::getKepena() const
{
    return kepena;
}

bool settings::getJoyena() const
{
    return joyena;
}

bool settings::getFrissonoff() const
{
    return frissonoff;
}

bool settings::getPontonav() const
{
    return pontonav;
}

bool settings::getCmdav() const
{
    return cmdav;
}

bool settings::getRobotkarena() const
{
    return robotkarena;
}

bool settings::getBalereszt() const
{
    return balereszt;
}

bool settings::getBalman() const
{
    return balman;
}

QString settings::getChstyle() const
{
    return chstyle;
}

QString settings::getModename()
{
    return modename;
}
