#ifndef LEJATSZAS_H
#define LEJATSZAS_H

#include <QDialog>
#include <QTimer>
#include <QDomDocument>

namespace Ui {
class Lejatszas;
}

class Lejatszas : public QDialog
{
    Q_OBJECT

public:
    explicit Lejatszas(QWidget *parent = nullptr);
    ~Lejatszas();

    bool getKuld() const;
    bool getOlv() const;
    bool getJoy() const;
    bool getGuiUpdate() const;
    long getRekordszam() const;
    QList<long> *getIdsp() const;
    QList<QString> *getKuldendop() const;
    QList<QString> *getOlvasottp() const;
    QList<QString> *getJoystickp() const;

    long getNowID() const;
    QString getNowKuldendo() const;
    QString getNowOlvasott() const;
    QString getNowJoystick() const;
    void updateNow();


signals:
    void play();
private slots:
    void chooseFile();
    void startPlay();
    void lejatszas_idozito();
    void slidMove();


private:
    Ui::Lejatszas *ui;
    QString fileName;
    bool kuld,olv,joy,guiUpdate;
    QTimer *standard_speed;
    bool playing;

    QDomDocument *xml;
    QDomElement *node;
    long rekordszam;
    QList<long> ids;
    QList<QString> kuldendo;
    QList<QString> olvasott;
    QList<QString> joystick;

    long nowID;
    QString nowKuldendo;
    QString nowOlvasott;
    QString nowJoystick;

    QDomElement Child;
    QString tag;
    QDomNodeList nodes;
    QDomElement root;
    QDomElement Component;

    void getElements(long beg);
    long lastLoad=0;


signals:
    void xmlReload();



};

#endif // LEJATSZAS_H
