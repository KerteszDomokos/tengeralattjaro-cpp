#include "settings.h"
#include "ui_settings.h"

#include <QDebug>
#include <QTranslator>
#include <QFileDialog>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>


settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->qssszabvany->setOpenExternalLinks(1);

    sets = new QSettings("Aqualab megrendelő", "AquaLab");
    qRegisterMetaTypeStreamOperators<QList<bool> >("QList<int>");

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             ui->ipvalaszto->addItem(address.toString());
    }
ui->ipcim->setText(ui->ipvalaszto->currentText());

}

settings::~settings()
{
    delete ui;
}

void settings::hatfoly()
{
    frissites=ui->updateOnoff->isChecked();
    komm=ui->komm->isChecked();
    diagram=ui->diagramonoff->isChecked();
    grid=ui->grid->isChecked();
    uptime=ui->uptime->value();
    diagrammax=ui->diagrambuff->value();
}

void settings::resetUpt()
{

}

void settings::nyelvvalaszto()
{
    language=ui->nyelvvalaszto->currentText();
    ford();
}

void settings::grafset()
{

}

void settings::temavalaszt()
{
    QString mod = ui->temavalaszto->currentText();
    QString ss;
    if(mod=="Világos mód"|| mod=="Light mode"){
        QFile file(":/resources/lightmode");
        file.open(QFile::ReadOnly);
        ss = QString(file.readAll());
        file.close();
        modename="Világos mód";
    }
    else if(mod=="Sötét mód" || mod=="Dark mode"){
        QFile file(":/resources/darkmode");
        file.open(QFile::ReadOnly);
        ss = QString(file.readAll());
        file.close();
        modename="Sötét mód";
    }

    ui->temateszt->setStyleSheet(ss);
    st=ss;
}

void settings::masikTema()
{
    bool c=ui->masiktema->isChecked();
        ui->qssszabvany->setEnabled(c);
        ui->choose->setEnabled(c);
        ui->path->setEnabled(c);
        ui->nyelvvalaszto->setEnabled(-c);
}

void settings::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Megnyitás"), fileName,tr("Qt Style sheet fájlok (*.qss, *.QSS)"));

    ui->path->setText(fileName);
    readfile(fileName);
}

void settings::readfile(QString f){
    QFile file(f);
    file.open(QFile::ReadOnly);
    QString ss = QString(file.readAll());
    file.close();
    ui->temateszt->setStyleSheet(ss);
    st=ss;
}

void settings::getUserdata()
{
}

void settings::ipupd()
{
    ui->ipcim->setText(ui->ipvalaszto->currentText());
    ipedit();
}

void settings::ipedit()
{
    ip=ui->ipcim->text();
    QHostAddress i=QHostAddress(ip);
    qDebug()<<i;
    if(i.protocol()==QAbstractSocket::IPv4Protocol){
        ui->ipcim->setStyleSheet("QLineEdit{background-color:#5cf054;}");
    }else{
        ui->ipcim->setStyleSheet("QLineEdit{background-color:#ff3d3d;}");
    }
}

QString settings::getModename() const
{
    return modename;
}

QString settings::getIp() const
{
    return ip;
}

void settings::ford()
{
    if(language=="English"){
        QTranslator translator;
        qDebug()<<translator.load(":/languages/megrendelo-gui_en_EN.qm");
        qApp-> QCoreApplication::installTranslator(&translator);
        qDebug()<<"Angol";
        ui->retranslateUi(this);
    }
    if(language=="Magyar"){
        qDebug()<<"Magyar";
        ui->retranslateUi(this);
    }
}

QString settings::getSt() const
{
    return st;
}

QString settings::getLanguage() const
{
    return language;
}

QString settings::getFileName() const
{
    return fileName;
}

bool settings::getMasiktema() const
{
    return masiktema;
}

int settings::getDiagrammax() const
{
    return diagrammax;
}

int settings::getUptime() const
{
    return uptime;
}

bool settings::getGrid() const
{
    return grid;
}

bool settings::getDiagram() const
{
    return diagram;
}

bool settings::getKomm() const
{
    return komm;
}

bool settings::getKep() const
{
    return kep;
}

bool settings::getFrissites() const
{
    return frissites;
}
