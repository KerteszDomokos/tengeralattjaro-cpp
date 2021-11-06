#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <settings.h>
#include <lejatszas.h>

#include <thread>
#include <QSettings>
#include <QChartView>


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
    void openLejatszas();
    void goPlay();
    void stopPlay();

private:
    void getUserdata();
    void saveUserdat();
    void kommst();


    Ui::GUI *ui;
    settings *set;
    std::thread *kommpointer;
    QList<double> olvasott; QString olvasottNat;
    QList<double> olvasottList;
    long UID=0; long commentID; long felIDnull;
    QList<double> xteng; QList<double> yteng;
    QList<double> motatlag,homat,zavat,phat,redat,vezat,arsat;
    QList<double> ido;
    int uptime=30;//updatetime
    QSettings *sets;


    bool frissites, kep,komm,diagram,grid;
    int diagrammax;
    bool masiktema;
    QString fileName;
    QString language;
    QString currst;
    QString st, modename;
    QString ip;
    bool settingsOpened=0;
    QList<bool> bdats;

    Lejatszas *lejatszas;
    bool play=0;
    bool playopen=0;



};
#endif // GUI_H
