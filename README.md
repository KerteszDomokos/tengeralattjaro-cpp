# Tengeralattjaro-cpp

A tengeralattjáró projekt szoftveres hátterének fejlesztése zajlik itt.

# A programokról
A projektem nem nyilvános, így a kódok terjesztése tilos! Amennyiben másik felhasznló is szeretne hozzáférést kérni a ropo-hoz, kérjen hozzáférés az alábbi linken keresztül: https://docs.google.com/forms/d/1wjkiEEXhBRLhWbO0bBj651J_wT-xS9aCB350i4ifadg/edit?usp=sharing 

Amennyiben kérdésük van a kódokkal kapcsolatban az [Issues](https://gitlab.com/krtdm/tengeralattjaro-cpp/-/issues) menüben, vagy emailban tudják feltenni.

### Honlap
A projekt honlapja az [aqualab.hu](https://www.aqualab.hu), ezt szintén én fejlesztettem ki. A honlapon lefordított programok letöltésére is van lehetőség. A program dokumentációja is elérhető a weboldalon, bejelentkezés után.

### Neumann verseny

A repo csak a programok forráskódját tartalmazza, az előre összeállított csomagokat a projekt saját fejlesztésű honlapjáról [aqualab.hu](https://www.aqualab.hu) tölthetik le. Fontos, hogy a forráskód nem nyilvános, és üzleti titkokat tartalmaz, így ezt tilos bármilyen formában terjeszteni tilos. 
A commit-ok segítségével végigkísérhetik a fejlesztés menetét, mivel a kezdeti fejlesztések óta dokumentálom a fejlesztéseket. Ehhez szükséges a Git verziókezelő alapszintű ismerete.

### A repo felépítése
Az src-py mappában található a fedélzeti Raspberry Pi számítógépen futó python program található. Ez a fedélzeti arduino-val, és a vezérlőegységgel történő kommunikációért, és bizonyos adatok (I2C) adatok begyűjtéséért felelős.  
Az src-cpp mappában találhatók a C++ nyelven írt kódok, melyek az alábbiak:  
- Az aruduino mappában a fedélzeten futó kód, és a vezérlőegység hardveres részének kódja található
- A vezerloegyseg-gui mappában található a lefordítva is nyilvánosságra hozott program, mely a kommunikációt, a vezérlést, és a beérkező adatok megjelenítésést végzi. A grafikus felület a Qt keretrendszert használja, és képes a mintaként a fordított csomagba mellékelt .al merülési naplók megjelenítésére. 
- A megrendeloi-gui mappábana  jelenleg még fejlesztés alatt álló, megrendelőknek készülő, némileg letisztultabbra, könnyebben kezelhetőre, és nyilvánosra tervezett projekt fájljai találhatóak.
- A cpp mappában is megtalálhatók néhol python programok, ezek a GUI felületbe ágyazva végeznek el bizonyos kommunikációs feladatokat, melyeket a C++ sajátosságai miatt nem volt érdemes átírni.


