# AquaLab - Robot tengeralattjáró ügyfél felület dokumentáció
A program a legtöbb monitor típust támogatja, a legtöbb windows operációs rendszerrel együtt. A rendszer beépített angol nyelvet tartalmaz, mely a beállításokból elérhető.


## Telepítés  

**A telepítő futtatásához szükséges lehet a windows defender felugró figyelmezető ablakát bezárni. A programban nincsenek rosszindulatú kódok.**
A telepítéshez kövesse a telepítő utasításait! A rendszer telepítője létrehoz asztai ikont, és a start menüből is elérhetővé válik a program.  
Amennyiben szeretné eltávolítani, úgy törölheti a telepítési mappát, vagy futtathatja a windows eltávolító eszközét. 
## Kompatibilitás

A programok az alábbi rendszereken kerültek tesztelésre:
- Windows 10 Pro (10.0.19042.1288)
- Windows 10 Home  <br>
*Az összes számítógép x64-es architektúrájú processzorral rendelkezik*

A program kompatibilis továbbá:
- Windows 8.1
- További Universal Windows Platform 10 részét képező operációs rendszerek  
<br>
Fordítási adatok: Qt 5.15.2 MinGW 64 bit

## Fő felület elemei
- A bal felső sarokban találhatjuk az élő kamerakép helyét, ez azonban nem visszajátszható felvétel fájlból, mivel így túl nagy lenne a fájlok mérete.
- A felület jobb oldalán található fehér részen jelennek majd meg a grafikai elemek, és 3D-s animációk. Jelenleg technikai okokból nem tudunk a QtQuick3D modullal dolgozni.
- Az adatok boxban találhatóak meg a legfontosabb adatok.
  - Az alapvető működési adatok a fedélzeti adatokat tartalmazzák:
    - A számítógép kihasználtság százalékban mutatja meg, hogy mekkora a fedélzeti számítógép RAM és CPU használata.
    - A mélység az ultrahangos távolságmérővel végzett mélységmérés eredménye. (A szenzor nem minden merülésnél van bekötve az elektronikai rendszerbe)
    - A belső hőmérséklet adatból megtudhatjuk hogy a fedélzeten, a testen belül mekkora a hőmérséklet.
  - A Szenzoradatok között találjuk azokat az értékeket, melyek a vízminőség adatokból érhetőek el. A rendszer itt mérési zajt jelenít meg (azok közül csak a reális értékeket)
  - A felvétel beállításainál megadhatjuk hogy az élő adatokat hova mentse a rendszer. A rögzítést a menüszalag Rögzítés -> rögzítés pipálható funkcióval kapcsolhatjuk be.
    - A mentés helyének megváltoztatása gombbal megnyithatók a beállítások
    - A maximum esemény beállításokor meghatározhatjuk, hogy hány rekord menthető a egy mentési fájlba
    - A megjegyzés most-al szembeni Most gomb a megnyomsá pillanatában hozzáfűzi a felvételhez a szövegbeviteli helyre írt üzenetet, melyet az Add gombbal fűzhetünk hozzá

  - A betöltéskor üres grafikonon tetszőleges adatokat jeleníthatünk meg
    - Az x és y tengelyhez egyaránt kiválaszthatjuk a kívánt adatokat, ahol a beállításokban megadott mennyiségű adatot megjeleníti.
    - A betöltés gombbal jeleníthetjük meg a kiválasztott értékeket
    - A mentés képként funkcióval egy tetszőleges helyre menthetjük képként a grafikont.
- A kép alján található Frissítés ID a felület frissítésének számát jeleníti meg.

## Beállítási lehetőségek
A beállításokat a felső menüből a Fájl->Beállítások útvonalon, vagy az Alt+s billentyűparancscsal érheti el. 
A Beállítások ablak bezárás és a mégse gomb megnyomása esetén elfelejti a beállításokat, az OK megnyomásakor azonban a alkalmazza azokat.  
- A háttérfolyamatok beállításánál lehetőség van olyan beállítások elvégzésére is melyek a felhasználót közvetlenül nem érintik.
    - A felület frissítésének kikapcsolása nem ajánlott, mivel ez garantálja, hogy a megjelenített értékek a legfrissebbek. Kikapcsolásakor a frissítés megszűnik, és az automatizmusok, és a vezérlő módosításai sem kerülnek továbbításra az eszközhöz.
    - Az érkező adatok frissítési idejének a beállítása esetén az állítható be, hogy a felületen milyen időközönként kerülnek frissítésre és begyűjtésre az adatok. A túl alacsony érték nagyobb számítási kapacitást igényel, a nagyobb esetében pedig ritkában frissülnek az adatok. A reset gombbal visszaállíthatjuk az alapértelmezett(20) értéket. *A beállítást millisekundumban kell értelmezni. 1sec=1000microsec*
    - A kép folyamat letiltása esetén a folyamat leáll, bekapcsolás esetén elindul.
    - A kommunikációs rész másik módszert használ a párhuzamos futás biztosításához, a szálakat (thread). Ennek engedélyezése esetén automatikusan újraindul a folyamat.
    - A Diagram grid kikapcsolása jelenleg még nem elérhető, de ezzel a diagramot lehet személyreszabni.
- A Megjelenés és egyéb fülön jelenleg a felület megjelenését állíthatjuk be. A funkciók az alábbiak:
    - Az alapértelmezett témák alatt a legördülő menüből választható ki a kívánt beállítás. Az előzetes képe a Stílus példa mezőben megjelenik (itt adódhatnak hibás megjelenítések)
    - Amennyiben a nem alapértelmezett téma választása be van jelölve, aktívvá válik az egyéb témák. Itt kiválaszthatunk egy szabványos QT style sheet fájlt. Ez azt jelenti, hogy a css-hez hasonló formátumu fájl kiválasztása után az abban megadottak kerülnek aktiválásra.
- A kommunikáció beállításoknál lehetőségünk van beállítani a számítógép IP címét. Az automatikus szkennelések esetén a számítógép elérhető kaposolatait találjuk
- A felvétel beállításai boxban a mentés helyét állíthatjuk be.
- Nyelvi beállításoknál kivaálszthatjuk a felület angol fordítását is.
**A beállítésok többségénél elérhető a What's this funkció, amivel elérhetjük a rövid leírását a funkciónak**

## Lejátszási ablak
- Legfelül kiválaszthatjuk a lejátszandó fájlt, melyet a rögzítés használatával tudunk létrehozni, kiterjesztése pedig .al
- A fájl betöltésére kattintva a rendszer felméri és betölti a fájlt. *Amennyiben túl nagy a fájl, nem a teljeset tölti be, csupán az első száz rekordot. Ez azt jelenti, hogy száz adatcsomag szerepel a gyorsítótárban, ennyit lehet azonnal lejátszani, atöbbi adathoz szükség van a betöltésre. Ezt a program automatikusan elvégzi*
- A megjelenítési beállítáok egyenlőre nem elérhetőek, csak az összes adat lejátszására van lehetőség.
- Az XML fájl fülön böngészhetünk  a nyers fájlban
- Legalul a rekordok számát láthatjuk, ez a fájlban található mentett események száma.
- Az idővonalon a fájlban navigálhatunk előre, hátra, a betöltött adatok ilyenkor folyamatosan változnak a kívént tartományon belül. *A betöltéskor a lejátszásban kis megakadás az újab adatok betöltésekor várható*
- A lejátszás sebessége funkció egyenlőre nem elérhető.
- A play ikonnal ellátott gombra kattintva elindul a történésekkel egy sebességben. A grafikonok ilyenkor is elérhetőek, és valós adatokat mutatnak.
