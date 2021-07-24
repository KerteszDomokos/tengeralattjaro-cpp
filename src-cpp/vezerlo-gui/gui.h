#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QString>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
    QList<double> olvasott;
    QList<double> elozoOlvasottList;
    QString pypath="C:/Users/Gábor/AppData/Local/Programs/Python/Python38-32/python.exe";
    QString keppath="G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\python-files\\kep.py";
    QString joypath="G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\python-files\\joystick.py";
    //Üzenőfelület - 1:message, 2:warning, 3:error
    void msg(QString txt, int priority);

public slots:
    void closeApp(){close();}
    void update();
    void fps();
    void cmdSlot(); //if the cmd_p line text has an enter
    void openCmd();
    void closeCmd();
    void motorNull();

private:
    Ui::GUI *ui;
    QString commands(QString comm) ;
    QString stK();
    QString stJ();
    QList<double> conv(QString str);
    void joydat();
    QList<double> joystickAdatok;
    QList<double> get_joystickAdatok();
    QProcess *pr ;
    QProcess *pr2 ;
    QString elozoOlv="";
public:
    QString comH="comm - teszt parancs\nexit - program bezárása és kilépés\nPID(joy/kep) - kép vagy joy folyamat PID\nstop(Joy/Kep) - kép vagy joy folyamat megölése\ngetJoy - joystick adatai lekérése adott pillanatban\nstart(Kep/Joy) - elindítja a folyamatot ha az még nem fut\n";

};


#endif // GUI_H
