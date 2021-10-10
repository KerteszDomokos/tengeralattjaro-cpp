#include "lejatszas.h"
#include "ui_lejatszas.h"

#include <QFileDialog>
#include <QDebug>

Lejatszas::Lejatszas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Lejatszas)
{
    ui->setupUi(this);
}

Lejatszas::~Lejatszas()
{
    delete ui;
}

void Lejatszas::chooseFile()
{
    fileName = QFileDialog::getExistingDirectory(this,tr("AquaLab fájlok"), fileName);

    ui->filenametxt->setText(fileName);
}

void Lejatszas::startPlay()
{
    play();
}
