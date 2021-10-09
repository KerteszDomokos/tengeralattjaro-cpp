#include "felvetel.h"
#include "ui_felvetel.h"

#include <QFileDialog>

Felvetel::Felvetel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Felvetel)
{
    ui->setupUi(this);
}

Felvetel::~Felvetel()
{
    delete ui;
}

void Felvetel::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Felvétel megnyitása"), "", tr("AquaLab fájlok (*.al)"));
}
