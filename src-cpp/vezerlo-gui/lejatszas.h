#ifndef LEJATSZAS_H
#define LEJATSZAS_H

#include <QDialog>

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

signals:
    void play();
private slots:
    void chooseFile();
    void startPlay();


private:
    Ui::Lejatszas *ui;
    QString fileName;
    bool kuld,olv,joy,guiUpdate;
};

#endif // LEJATSZAS_H
