#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

    bool getFrissites() const;
    bool getKep() const;
    bool getKomm() const;
    bool getDiagram() const;
    bool getGrid() const;
    int getUptime() const;
    int getDiagrammax() const;
    bool getMasiktema() const;
    QString getFileName() const;
    QString getLanguage() const;
    QString getSt() const;

private slots:
    void hatfoly();
    void resetUpt();
    void nyelvvalaszto();
    void grafset();
    void temavalaszt();
    void masikTema();
    void chooseFile();
    void ford();
    void readfile(QString f);
    void getUserdata();



private:
    Ui::settings *ui;

    bool frissites, kep,komm,diagram,grid;
    int uptime, diagrammax;
    bool masiktema;
    QString fileName;
    QString language;
    QString st, modename;
    QSettings *sets;


};

#endif // SETTINGS_H
