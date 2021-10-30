#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <settings.h>

#include <thread>


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

private:
    Ui::GUI *ui;
    settings *set;
    std::thread *kommpointer;
    QList<double> olvasott; QString olvasottNat;
    QList<double> olvasottList;


};
#endif // GUI_H
