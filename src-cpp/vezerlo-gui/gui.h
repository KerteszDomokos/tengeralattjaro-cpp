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

public slots:
    void closeApp(){close();}
    void update();
    void fps();
    void cmdSlot(); //if the cmd_p line text has an enter
    void openCmd();
    void closeCmd();
    QString pypath="C:/Users/Gábor/AppData/Local/Programs/Python/Python38-32/python.exe";
    QString keppath="G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\program-datas\\kep.py";
    QString joypath="G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\program-datas\\joystick.py";

private:
    Ui::GUI *ui;
    QString commands(QString comm) ;
    QList<double> conv(QString str);
    void joydat();
    QList<double> joystickAdatok;
    QList<double> get_joystickAdatok();
    QProcess *pr ;
    QProcess *pr2 ;
    QString elozoOlv="";


};


#endif // GUI_H
