# Tengeralattjaro-cpp

A tengeralattjáró projekt cpp fejlesztése

# A programokról
A projektem nem nyilvános, így a kódok terjesztése tilos! Amennyiben másik felhasznló is szeretne hozzáférést kérni a ropo-hoz, kérjen hozzáférés az alábbi linken keresztül: https://docs.google.com/forms/d/1wjkiEEXhBRLhWbO0bBj651J_wT-xS9aCB350i4ifadg/edit?usp=sharing 

Amennyiben kérdésük van a kódokkal kapcsolatban az [Issues](https://gitlab.com/krtdm/tengeralattjaro-cpp/-/issues) menüben, vagy emailban tudják feltenni.

## Régi github repo adatai
### Felépítés
Az src-py mappában vannak a pyton programok. A main.py az, amely egyedül futtatandó a vezérlőegységnél. Az src-py/Fedelzet/runer.py pedig a fedélzeti rpi-n futtatandó fájl. Látható hogy sok folyamat van. A vezérlőnél a gui a fő folyamat, ott kerül a kamera képe is vételre, a mindkét fájlban megtalálható tcp függvény nem használt, de még nem töröltem őket, anno így működött. A log fájlokba a [e27ee79](https://github.com/KerteszDomokos/Tengeralattjaro-RUV/commit/e27ee795e17dce0e946990cf4969732d3a567d7a) óta rossz sorrendben kerülnek mentésre az adatok de az időbályeg miatt viszonylag követhető. Magát a guit a KV files mappában található 0.4.kv fájlban fejtem ki, mivel a kivy gui rendszere támogatja a külön fájlba felület írást.