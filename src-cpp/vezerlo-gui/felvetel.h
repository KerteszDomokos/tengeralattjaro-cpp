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

    QString getFileName() const;
    void setFileName(const QString &value);
    bool getOlvIN() const;
    bool getKuldIN() const;
    bool getKonzIN() const;
    bool getJoyIN() const;
    bool getKepIN() const;
    bool getDefPathIN() const;

    QString getFullPath() const;

private slots:
    void chooseFile();
    void apply();
    void elvet();
    void ok();
    void filenameUpdate();


private:
    Ui::Felvetel *ui;
    QString fileName;
    QString LfileName;
    QString fullPath;
    bool joyIN, olvIN,kuldIN, konzIN,defPathIN,kepIN;
    void generateFilename(int id);
    int rid;
};

#endif // FELVETEL_H
