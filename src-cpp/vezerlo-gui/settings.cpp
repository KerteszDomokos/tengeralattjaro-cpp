#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>

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

void settings::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this,tr("Megnyitás"), fileName,tr("Aqualab fájlok (*.al, *.AL, *.*)"));

    ui->filename_tema->setText(fileName);

    msg("Lejátszásnál kiválasztott fájlnevet lekérheti a parancssorból",1);
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QString ss = QString(file.readAll());
    file.close();
    ui->temateszt->setStyleSheet(ss);
}

QString settings::ujfileName()
{
    return fileName;
}
