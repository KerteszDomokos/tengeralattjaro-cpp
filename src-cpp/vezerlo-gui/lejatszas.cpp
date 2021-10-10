#include "lejatszas.h"
#include "ui_lejatszas.h"

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
