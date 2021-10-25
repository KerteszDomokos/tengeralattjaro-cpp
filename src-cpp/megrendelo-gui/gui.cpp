#include "gui.h"
#include "ui_gui.h"

#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QDebug>

#include <settings.h>

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    forditas("English");

}

GUI::~GUI()
{
    delete ui;
}

void GUI::forditas(QString lang)
{
    qDebug()<<"Meghívva";
    if(lang=="English"){
        QTranslator translator;
        qDebug()<<translator.load(":/languages/megrendelo-gui_en_EN.qm");
        qApp-> QCoreApplication::installTranslator(&translator);
        qDebug()<<"Angol";
        ui->retranslateUi(this);
    }
    if(lang=="Magyar"){
    ui->retranslateUi(this);
    }

}

void GUI::open_beallitasok()
{
    set=new settings;
    set->show();
}

