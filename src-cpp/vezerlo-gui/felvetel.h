#ifndef FELVETEL_H
#define FELVETEL_H

#include <QDialog>
#include <QFileDialog>
#include <QString>


namespace Ui {
class Felvetel;
}

class Felvetel : public QDialog
{
    Q_OBJECT

public:
    explicit Felvetel(QWidget *parent = nullptr);
    ~Felvetel();

private slots:
    void chooseFile();

private:
    Ui::Felvetel *ui;
    QString fileName;
};

#endif // FELVETEL_H
