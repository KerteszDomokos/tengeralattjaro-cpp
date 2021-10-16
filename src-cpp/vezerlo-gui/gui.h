#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QString>
#include <QProcess>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QElapsedTimer>
#include <QtXml>
#include <QTextStream>
#include <QDomElement>
#include <QDomDocument>
#include <felvetel.h>
#include <lejatszas.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
    double rad(double degree);//radiánná konvertálás

private slots:
    void closeApp(){close();}
    void update();//adatok és folyamatosan futó értékek átállítása
    void fps();//Kép frissítés
    void cmdSlot(); //ha a cmd_p beviteli felület entert érzékel
    void openCmd();//cmd ablak megnyitása
    void closeCmd();//cmd ablak bezárása
    void motorNull();//motorok lenullázása (hardpot off, egyenlomot off)
    void updateKommData();//Kommunikációs adatok frissítése a mutex val-ból
    void serkom();//soros kommunikáció olvasás
    void serKeres();//soros portok scannalése
    void serConn();//soros csatlakozés a kivákaszott porthoz
    void serDeconn();//soros lecsatlakozás a csatlakozott eszközről
    QString stK();//start kép folyamat
    QString stJ();//start joystick folyamat
    void ponton_stop();//pontonhajó motor lenullázása
    void ponton_egyenes();//ponton kormány egyenesbe
    void akksporolas();//spórolás beállítása
    void ballaszt_manualis_click();
    void ballaszt_emelkedes();
    void ballaszt_erzekenyseg();
    void talca_kinyit();
    void talca_becsuk();
    void ballasztBalmin();
    void ballasztBalmax();
    void ballasztBalk();
    void ballasztJobbk();
    void ballasztJobbmin();
    void ballasztJobbmax();
    void set_darkmode();
    void set_lightmode();
    void mentes();
    void mentesDialog();
    void felvAccept();
    void lejatszasOpen();
    void goPlay();
    void stopPlay();
    void stopFelvetel();
    void startRec();
    void msg(QString txt, int priority);//üzenet kiírása a gui konzolra - Üzenőfelület - 1:message, 2:warning, 3:error
    void cl();



private:
    Ui::GUI *ui;
    QString commands(QString comm) ;//parancssor parancs kereső függvény
    QList<double> conv(QString str);//Szóközzel elválasztott szöveg konvertálása double listába
    QList<int> convInt(QString str);//Szóközzel elválasztott szöveg konvertálás int listába
    void joydat();//joystick adatok olvasása fájlból
    QList<double> get_joystickAdatok();//joystick adatok lekérése
    void ment();
    QString listToStr(QList<double> l);
    QString listToStr(QList<int> l);
    QString generatePath(int id);


    QProcess *pr ;//joystick process cl pointer
    QProcess *pr2 ;//kép process cl pointer
    QString elozoOlv="";//előző olvasott adat összehasonlításhoz
    QString bejovoFriss="";//legfrissebb bejövő adat szövegben
    QList<double> kuldendoFriss;//a küldendő adatok listája a legfrissebb adatokkal
    QSerialPort *mSerial;//soros osztály pointer
    QList<int> serDat={0,0,0};//olvasott soros adatok legfrissebb
    QList<int> serDatElozo;//olvasott soros adatok előző csomag
    QList<double> joystickAdatok;//a joystick legfrissebb adatai
    QList<QSerialPortInfo> mSerialPorts; //elérhető soros portok, nem a legfrissebbek, scan gomb
    QList<double> elozoOlvasottList;//előző olvasott adatcsomag listában
    QList<double> olvasott;//legfrissebb olvasott adatcsomag listában
    int kepHiba;
    bool mentes_onoff=0;
    ulong mentid=0;
    QDomDocument *ment_doc;
    QTextStream *xmlContent;
    QFile *xmlFile;
    QDomElement *root_xml;
    Felvetel *widget;
    bool joyIN, olvIN,kuldIN, konzIN,defPathIN,kepIN;
    QString felvPath;
    QString felvPathGyok;

    Lejatszas *lejatszas;
    bool playing=0;
    bool joydat_play;
    bool kuld_play;
    bool olv_play;
    bool guiupdate_play;

    bool lejatszasOpened;
    bool felvetelOpened;






public: //hösszú szöveges változók
    //a parancssor helptxt-je:
    QString comH="comm - teszt parancs\nexit - program bezárása és kilépés\nPID(joy/kep) - kép vagy joy folyamat PID\nstop(Joy/Kep) - kép vagy joy folyamat megölése\ngetJoy - joystick adatai lekérése adott pillanatban\nstart(Kep/Joy) - elindítja a folyamatot ha az még nem fut\n";
    QString joypath="G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\python-files\\joystick.py";
    QString keppath="G:\\Privát adatok\\.Programozás\\Projektek\\Tengeralattjáró\\v1 - Github\\tengeralattjaro-cpp\\src-cpp\\vezerlo-gui\\python-files\\kep.py";
    QString pypath="C:/Users/Gábor/AppData/Local/Programs/Python/Python38-32/python.exe";



};

#endif // GUI_H
