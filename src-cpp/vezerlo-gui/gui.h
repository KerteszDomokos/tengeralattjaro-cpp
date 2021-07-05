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
public slots:
    void closeApp(){close();}
    void update();
    void cmdSlot(); //if the cmd_p line text has an enter
    void openCmd();
    void closeCmd();

private:
    Ui::GUI *ui;
    QString commands(QString comm) ;
    QList<double> conv(QString str);
    void joydat();
    QList<double> joystickAdatok;
    QList<double> get_joystickAdatok();
    QProcess *pr = new QProcess(this);
    QString elozoOlv="";


};


#endif // GUI_H
