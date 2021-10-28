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
    

