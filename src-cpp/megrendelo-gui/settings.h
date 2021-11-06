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
    QString getIp() const;
    QString getModename() const;
    QString getCurrtem() const;
    QString getMentespath() const;

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
    void ipupd();
    void ipedit();
    void getUserdat();
    void applySets();
    void chooseMentes();
    void generatePath(int id);



private:
    Ui::settings *ui;

    bool frissites, kep,komm,diagram,grid;
    int uptime, diagrammax;
    bool masiktema;
    QString fileName;
    QString language;
    QString currtem;
    QString st, modename;
    QSettings *sets;
    QString ip;
    QList<bool> bdats;
    QString mentespath;
    int rid;


};

#endif // SETTINGS_H
