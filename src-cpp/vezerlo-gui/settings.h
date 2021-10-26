#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();
    QString getChstyle() const;//getter to chstyle

private slots:
    void chooseFile(); // témafájl választás
    void otherThema(); // másik téma bejelölés ellenőrzése
    void modvalasztas(QString mod); // alapértelmezett témák közötti választás
    void beavleh(); //a beavatkozási lehetőségek beállítása módosítások esetén meghívandó slot
    void beav_reset(); //a beavatkozási beállítások visszaállítása
    void hatfoly(); //A háttérfolyamatok beállításakor meghívandó
    void updatetime_reset(); //Az updatetimeot reseteli 20-ra

signals:
    void msg(QString dat, int pr);//a konzolüzenetek signalja

private:
    Ui::settings *ui;
    QString fileName;//téma fájl elérési út
    QString chstyle;//Az új téme teljes beolvasott szövege (lásd: getter)
};

#endif // SETTINGS_H
