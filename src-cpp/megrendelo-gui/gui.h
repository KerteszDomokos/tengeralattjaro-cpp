#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <settings.h>

#include <thread>
#include <QSettings>


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
private slots:
    void forditas(QString lang="Magyar");
    void open_beallitasok();
    void kommdatUpdate();
    void upd();
    QList<double> conv(QString str);
    void kommentMost();
    void loadGraf();
    void applyUserdat();
    void notapplyUserdat();

private:

    void getUserdata();

    Ui::GUI *ui;
    settings *set;
    std::thread *kommpointer;
    QList<double> olvasott; QString olvasottNat;
    QList<double> olvasottList;
    long UID=0; long commentID; long felIDnull;
    QList<double> xteng; QList<double> yteng;
    QList<double> motatlag;
    QList<double> ido;
    int uptime=30;//updatetime
    QSettings *sets;


};
#endif // GUI_H
