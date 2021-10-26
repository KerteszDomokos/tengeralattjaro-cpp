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

    QString getChstyle() const;

private slots:
    void chooseFile();
    void otherThema();
    void modvalasztas(QString mod);
    void beavleh();
    void beav_reset();
    void hatfoly();
    void updatetime_reset();

signals:
    void msg(QString dat, int pr);

private:
    Ui::settings *ui;
    QString fileName;//téma fájl
    QString chstyle;
};

#endif // SETTINGS_H
