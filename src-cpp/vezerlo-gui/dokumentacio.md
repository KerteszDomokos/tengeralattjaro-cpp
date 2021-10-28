# Robot tengeralattjáró vezérlőfelület dokumentáció
A grafikus felületet az 1920 x 1080 pixeles monitorokra készült, így más méreteken a legnagyobb figyelem ellenére előfordulhatnak az egymásracsúszások.
<br>
<br>

## Fő felület elemei
A program megnyitása után megjelenő számos grafikai megjelenítő és vezérlő elem funkcióinak magyarázata.  
A magyarázat balról-jobbra, fentről-le történik
- Alap grafikák box 
    - A kamera élő képe (első futtatáskor ide a várakozás kép kerül, később pedig az utolsó rögzített kép)
    - A műhorizont a dőlést jeleníti meg mind X mind Y tengely mentén. Amennyiben nem érkeznek adatok (felvételből vagy a robottól) 90°-os elfordulást mutat a képe
- A mélységérzékelő a adatai megjelenítő grafika átmenettel képes megjeleníteni a mélységet
- Az iránytő a fedélzeti mágnesérzékelő adatait jeleníti meg
- A radar adatai megjelenítő kísérleti felület, ez azonban sajnos nem működik megfelelően.
- A következő csoportban egy több ablakos felület található.
    - Érkező adatok  
        - A vezérlési adatok csoportban táblázatok találhatóak az érkező adatokkal. Itt a jó adatok zöld, a rosszak pedig piros hátérrel rendelkeznek. Ezek az adatokkal együtt frissülnek.
        - Jobb oldalon a képi kommunikáció és az alatta lévő piros vagy zöld hátterű, számot tartalmazó mezőben a fedélzeti egységről érkező képeket feldolgozó program adatai jelennek meg. A színes sávban a folyamat azonosítója (Process ID) található, a start gombbal pedig elindítható a folyamat.
        - A joystick kezelése is külön folyamatban történik, ezért a itt is -nél elérhetőek a képnél már megmagyarázott funkciók
        - Ezalatt egy szövegdoboz található, ahol a kísérleti radar adatai jelennek meg. Ezt a normál, stabilműködésnél figyelmen kívül lehet hagyni.
        - A táblázatok alatt egy alapesetben nullákat tartalmazó szövegdoboz található. Ebben jelennek meg nyersen az olvasott adatok. Itt láthatóak lejátszás közben is az adatok. 
        - Legalul egy másik hasonló doboz található, itt a küldendő adatok jelennek meg nyersen.
        - Az UID az Update ID rövidítése. Ez a szám mutatja, hogy a felület az indítás óta hányszor frissült. Segítségével bizonyos beállítások ellenőrizhetők akkor is, ha csak ez az érték változik az egész felületen.
    - Tesztelési adatoknál elsősorban a bemeneti vezérlőeszközök tesztelésére használható
        - A joystick gombjainak a lenyomását jeleníti meg. A joystick funkció csupán egyetlen eszközön került tesztelésre. Az adatok frissítése csak a lenti joystick teszt pipálásával történik meg.
        - A szövegdobozban a joystick nyers adatai jelennek meg.
        - A funkcióhoz az Érkező adatok tabon sikeresen el kell indítani a joystick folyamatot.
    - Áramköri vizualizáció egy jelenleg még nem elérhető funkció
- A Pontonhajó adatait tartalmazó csoport (a beállításokat ellenőrizze, ha inaktív a doboz)
    - A bal oldali csúszka a ponton motorját képes vezérelni.
    - A stop gombbal nulla állásba állítható a motor, a kormány egyenessel pedig a kormány állítható egyenes állásba
    - A kormányzást lehetővé tevő forgatható elem a kormánylapát állását szabályozza a pontonhajón.
- A zöld hátterű felületen a fedélzeti robotkar vezérelhető. A kék téglalapok a kar állandő részeit jelentik, míg a forgatható elemek a motorokat. A rendszer ezek alapján állítja be a motorokat avíz alatt.
    - A szövegdobozban a robotkar adatai jelennek meg, ha a jobboldali frissítés be van kapcsolva.
- A vezérlés csoportban az alap funkciók vezérlést tehetjük meg.
    - A motorok csoportban az első csúszkával a baloldali motort vezérelhetjük, a másodikkal a jobboldalit. A harmadik akkor használható, ha az egyenlő motorok funkció be van kapcsolva. Ekkor a két motor ereje egyenlő lesz, és a harmadik csúszkával vezérelhetőek együtt.
    - A második kettő csúszka a döntőmotorok vezérlésére szolgál. Ezek a tengeralattjáró farán alul és felül elhelyezett motorok, melyekkel a test dőlése szabályozható.
    - A szövegdobozban a motorok beállított értékei találhatóak, ezek a visszacsatolást segítik.
    - A szövegdoboz alatt található néhány kapcsoló:
        - Hardveres Pot: A motorok vezérlésére szolgáló rendszert aktiválja, vagy deaktiválja. Ha be van kapcsolva, a csúszkák egérrel nem vezérelhetőek.
        - DMot Joy: Akkor kapcsolható be, ha a Döntőmotorokat joystick segítségével szeretnénk vezérelni. Amennyiben nem elérhető a joystick, a legutóbbi elérhető értéket jeleníti meg.
        - Egyenlő motorok: Amennyiben be van kapcsolva a harmadik csúszka aktív lesz, így a két motor együtt vezérelhető a harmadik csúszkával.
        - A nullázás gomb a motorkat azonnal leállítja, az egyenlő motorokat és a hardveres vezérlést kikapcsolja
    - A tálca felirat alatt található a test alatt elhelyezkedő tálca vezérlője. Amennyiben az aktív engedélyezve van, a tálca mozgatható a potméterrel, és a gombok segítségével. *Egyenlőre a tálca hardver nem elérhető, azonban a szoftverekben már elérhető a vezérlése*
- Az áramellátás mellett található a fedélzeti áramellátás beállítását lehetővé tevő néhány beállítás. Az egyedüli működő funkció az erőforrásspórolás, ekkor bizonyos funkciókat letilt a rendszer (pl. kamera)
- Az egyéb menüpontban beállítható, hogyha a testet a hátára borítjuk a motorok haladási irányhoz képest oldala megváltozik. Ez a kapcsoló elvégzi a beállítást. A hűtéshez tartozó csúszkával a hűtőventillátor erősségét állíthatjuk be.
- A vezérlő soros kommunikáció menüpont alatt átállíthatjuk, hogy a rendszer melyik soros portra csatlakoztatott eszközzel próbáljon meg kommunikációt folytatni a motorok vezérlési adatát érzékelve. A hardveres pot funkcióhoz itt kell csatlakoztatni az elkészült eszközt (*Egyes esetekben a CH340 soros illesztő driver telepítése a külső hardveres eszközzel való kommunikációhoz. Amennyiben a funkció nincsen használatban erre nincsen szükség*)
    - A scan gombra kattintva az elérhető soros portok frissülnek, ekkor kiválasztható a megfelelő a legördülő listából.
    - A csatlakozás gombbal megkezdhetjük a kommunikációt. Ekkor a rendszerüzenet szövegdobozban a sikeres csatlakozásnak kell megjelennie, a soros nyers adatok boxban pedig a folyamatosan frissülő nyers adatoknak.
    - A lecsatlakozás gombbal megszakíthatjuk a kommunikációt.
- A fedélzeti szoftver vezérlés cím alatt a fedélzeti számítógépen és arduino-n futó kód beállításait végezhetjük el. 
    - Az élő képet be kell jelölni abban az esetben, ha a szeretnénk hogy az élő kép küldése megkezdődjön. **Ehhez a funkcióhoz a Kép kommunikációt szükésges elindítani a vezérlési adatok box-ban**
    - A radar szkennelés egy kísérleti funkciót indít be, melyhez a megfelelő hardverek csak bizonyos tesztek esetében vannak csatlakoztatva.
- A következő csoport a ballasztrendszer
- A rendszerüzenetek boxban a program szöveges üzeneteit találjuk. Három szinten (message, warning, error) jelennek meg az információk, az error üzenetekre nagyobb figyelmet fordítani.

## Beállítási lehetőségek
A beállításokat a felső menüből a Fájl->Beállítások útvonalon, vagy az Alt+s billentyűparancscsal érheti el. 
A Beállítások ablak bezárás és a mégse gomb megnyomása esetén elfelejti a beállításokat, az OK megnyomásakor azonban a alkalmazza azokat.  
Az ablak két fontos részből áll, az Általánosból, és a megjelenés és egyéb fülből.  
Általános:
- Beavatkozási lehetőségek csoportban a felületen elvégezhető beállításokat lehet korlátozni, illetve engedélyezni
    - A ballasztrendszer vezérelhető csúszkával manuálisan is, ez azonban kockázatos lehet. Itt letiltható a funkció.
    - A ballaszttartály teljes leeresztését engedélyező funkció. A teszteléseknél lehet szükség a beállításra, merülés közben nem ajánlott engedélyezni.
    - A robotkar vezérlésének letiltásával számítási kapacitást spórolhatunk. Ha a rendszerbe nincsen beépítve, érdemes letiltani.
    - A Parancssor elérhetővé tétele. A parancssorról bővebben is olvashatnak, itt speciális beállítások végezhetőek el, vagy belső adatok kérhetőek le.
    - A Ponthajó nem minden esetben kerül csatlakoztatásra, így amennyiben nem elérhető érdekes lehet letiltani.
    - Az alapértelmezettek visszaállítása a felhasználó által beállított értékeket elveti. Ez nem visszavonható.
- A háttérfolyamatok beállításánál lehetőség van olyan beállítások elvégzésére is melyek a felhasználót közvetlenül nem érintik.
    - A felület frissítésének kikapcsolása nem ajánlott, mivel ez garantálja, hogy a megjelenített értékek a legfrissebbek. Kikapcsolásakor a frissítés megszűnik, és az automatizmusok, és a vezérlő módosításai sem kerülnek továbbításra az eszközhöz.
    - Az érkező adatok frissítési idejének a beállítása esetén az állítható be, hogy a felületen milyen időközönként kerülnek frissítésre és begyűjtésre az adatok. A túl alacsony érték nagyobb számítási kapacitást igényel, a nagyobb esetében pedig ritkában frissülnek az adatok. A reset gombbal visszaállíthatjuk az alapértelmezett(20) értéket. *A beállítást millisekundumban kell értelmezni. 1sec=1000microsec*
    


