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


private slots:
    void hatfoly();
    void resetUpt();
    void nyelvvalaszto();
    void grafset();
    void temavalaszt();
    void masikThema();
    void chooseFile();

private:
    Ui::settings *ui;
};

/*

  <slot>hatfoly()</slot>
  <slot>resetUpt()</slot>
  <slot>nyelvvalaszto()</slot>
  <slot>grafset()</slot>
  <slot>temavalaszt()</slot>
  <slot>masikThema()</slot>
  <slot>chooseFile()</slot>

*/


#endif // SETTINGS_H
