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
