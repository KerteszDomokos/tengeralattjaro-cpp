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
    bool ujTema=0;
    QString ujfileName();

private slots:
    void chooseFile();
    void otherThema();
    void modvalasztas(QString mod);
signals:
    void msg(QString dat, int pr);

private:
    Ui::settings *ui;
    QString fileName;//téma fájl
};

#endif // SETTINGS_H
