#include "settings.h"
#include "ui_settings.h"

#include <QDebug>
#include <QTranslator>
#include <QFileDialog>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QDate>
#include <QTranslator>


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

getUserdat();
forditas(language);

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

void settings::getUserdat(){
    bdats=sets->value("booldatas").value<QList<bool>>();
    diagrammax=sets->value("diagrammax").toInt();
    fileName=sets->value("fileName").toString();
    language=sets->value("lang").toString();
    ip=sets->value("ip").toString();
    st=sets->value("Style").toString();
    currtem = sets->value("curs").toString();
    applySets();
}

void settings::applySets()
{
    ui->diagrambuff->setValue(diagrammax);
    ui->path->setText(fileName);
    ui->nyelvvalaszto->setCurrentText(language);
    ui->ipvalaszto->setCurrentText(ip);
    ui->ipcim->setText(ip);
    ui->temavalaszto->setCurrentText(currtem.toLatin1());
}

void settings::chooseMentes()
{
    fileName = QFileDialog::getExistingDirectory(this,tr("Felvétel megnyitása"), fileName);
    ui->mentespath->setText(fileName);
    int runID=0;
    QList<QString> fn;
    QDir d(fileName);
    QStringList files=d.entryList(QStringList()<<"*.al"<<"*.AL",QDir::Files);
    foreach(QString filename, files) {
        fn.append(filename);
    }
    for (int i=0; i<fn.length();i++){
        QString del = fn[i].replace(0,16,"").replace(2,3,"");
        for (int da=0; da<100;da++){
            QString c;
            if(da<10){c="0";}
            c=c+QString::number(da);
            if(del==c){
                runID=da+1;
            }
        }
    }
rid=runID;
generatePath(runID);

}

void settings::generatePath(int id)
{
    QString p=QDate::currentDate().QDate::toString("yy-MM-dd");
    QString nam="/merules"+p+"-";
    if(id<10){nam=nam+"0";}
    nam=nam+QString::number(id)+".al";
    ui->kovfile->setText("..."+nam);

    mentespath=fileName+nam;
}

QString settings::getMentespath() const
{
    return mentespath;
}

void settings::getall()
{
    hatfoly();
}

QString settings::getCurrtem() const
{
    return currtem;
}

void settings::resetUpt()
{

}

void settings::nyelvvalaszto()
{
    language=ui->nyelvvalaszto->currentText();
    forditas(language);
}

void settings::grafset()
{

}

void settings::temavalaszt()
{
    QString mod = ui->temavalaszto->currentText();
    QString ss;
    if(mod=="Világos mód" || mod=="Light mode"){
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
void settings::forditas(QString lang)
{
    if(lang=="English"){
        QTranslator translator;
        translator.load(":/languages/megrendelo-gui_en_EN.qm");
        qApp-> QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this);
    }
    if(lang=="Magyar"){
    ui->retranslateUi(this);
    }
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



void settings::ipupd()
{
    ui->ipcim->setText(ui->ipvalaszto->currentText());
    ipedit();
}

void settings::ipedit()
{
    ip=ui->ipcim->text();
    QHostAddress i=QHostAddress(ip);
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
        qApp-> QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this);
    }
    if(language=="Magyar"){
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
