#include "settings.h"
#include "ui_settings.h"

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

}

void settings::resetUpt()
{

}

void settings::nyelvvalaszto()
{

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
