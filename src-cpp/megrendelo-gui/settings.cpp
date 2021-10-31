#include "settings.h"
#include "ui_settings.h"

#include <QDebug>
#include <QTranslator>

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->qssszabvany->setOpenExternalLinks(1);
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

}

void settings::masikThema()
{

}

void settings::chooseFile()
{

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
