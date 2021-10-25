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

GUI::~GUI()
{
    delete ui;
}

