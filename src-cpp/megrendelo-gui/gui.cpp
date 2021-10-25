#include "gui.h"
#include "ui_gui.h"

#include <QLocale>
#include <QTranslator>
#include <QString>
#include <QDebug>

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);

    QTranslator translator;
    qDebug()<<translator.load("megrendelo-gui_en_EN",":/languages");
    qApp->installTranslator(&translator);

}

void GUI::open_beallitasok()
{
    set=new settings;
    set->show();
}

