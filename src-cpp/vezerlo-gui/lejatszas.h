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

private:
    Ui::Lejatszas *ui;
};

#endif // LEJATSZAS_H
