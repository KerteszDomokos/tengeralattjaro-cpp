#include "felvetel.h"
#include "ui_felvetel.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QDate>

Felvetel::Felvetel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Felvetel)
{
    ui->setupUi(this);

    LfileName=fileName;


}

Felvetel::~Felvetel()
{
    delete ui;
}

void Felvetel::chooseFile()
{
    message("Fájl választása",1);
    fileName = QFileDialog::getExistingDirectory(this,tr("Felvétel megnyitása"), fileName);
    valaszt();
}



void Felvetel::apply()
{
    joyIN=ui->joyin->isChecked();
    olvIN=ui->olvin->isChecked();
    konzIN=ui->konzin->isChecked();
    defPathIN=ui->alapertMentin->isChecked();
    kepIN=ui->kepin->isChecked();
    kuldIN=ui->kuldin->isChecked();
}

void Felvetel::elvet()
{
    fileName=LfileName;
    message("Beállítások elvetése",2);
}

void Felvetel::ok()
{
    generateFilename(ui->sorszam->value());
    apply();
    accept();
    close();
}

void Felvetel::filenameUpdate()
{
    generateFilename(ui->sorszam->value());
}

void Felvetel::acceptRec()
{
    mods();
    qDebug()<<maxdat;
    recStart();
    accept();
}

QString Felvetel::getFullPath() const
{
    return fullPath;
}

void Felvetel::generateFilename(int id)
{
    QString p=QDate::currentDate().QDate::toString("yy-MM-dd");
    QString nam="/merules"+p+"-";
    if(id<10){nam=nam+"0";}
    nam=nam+QString::number(id)+".al";
    ui->kovfile->setText("..."+nam);
    ui->sorszam->setValue(id);
    if(rid>ui->sorszam->value()){
        ui->sorszam->setStyleSheet("QSpinBox{background-color:red;}");
    }
    else{
        ui->sorszam->setStyleSheet("");
    }
    fullPath=fileName+nam;
}

void Felvetel::valaszt()
{
    ui->filenametxt->setText(fileName);
    int runID=0;
    QList<QString> fn;
    QDir d(fileName);
    QStringList files=d.entryList(QStringList()<<"*.al"<<"*.AL",QDir::Files);
    foreach(QString filename, files) {
        ui->fajlok->setText(ui->fajlok->toPlainText()+filename+"\n");
        fn.append(filename);
        }
    for (int i=0; i<fn.length();i++){
        QString del = fn[i].replace(0,16,"").replace(2,3,"");
        for (int da=0; da<100;da++){
            QString c;
            if(da<10){c="0";}
            c=c+QString::number(da);
            if(del==c){
                runID=da+1;
            }
        }
    }
rid=runID;
generateFilename(runID);

}

void Felvetel::setMaxdat(int value)
{
    maxdat = value;
    ui->ujfile->setValue(maxdat);
}

int Felvetel::getMaxdat() const
{
    return maxdat;
}

bool Felvetel::getDefPathIN() const
{
    return defPathIN;
}

void Felvetel::setDats(QString style)
{
    this->setStyleSheet(style);
}

void Felvetel::mods(){
    maxdat=ui->ujfile->value();
}

bool Felvetel::getKepIN() const
{
    return kepIN;
}

bool Felvetel::getJoyIN() const
{
    return joyIN;
}

bool Felvetel::getKonzIN() const
{
    return konzIN;
}

bool Felvetel::getKuldIN() const
{
    return kuldIN;
}

bool Felvetel::getOlvIN() const
{
    return olvIN;
}


QString Felvetel::getFileName() const
{
    return fileName;
}

void Felvetel::setFileName(const QString &value)
{
    fileName = value;
}
