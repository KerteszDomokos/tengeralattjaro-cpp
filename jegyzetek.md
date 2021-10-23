# Jegyzetek

## A kommunikációs csatornák adatai  
<br>

### Fedélzeti RPi &#8594; Vezérlőegység Rpi 
* TCP csatorna  
* Array, 30 elem

0: kommunikáció sikeressége  
1: belső víz magassága  
2: Mélység, hiba esetén 0, nem mért: előző érték  
3: error száma  
4: csp1 mérése  
5: Hőmérő 1 hőmérséklet (az ESC-hez!)  
6: Hőmérő 2 hőmérséklet (az ESC-hez!)  
7: Hőmérés DHT  
8: Páratartalom  
9: Motor bal mért erő (nullért kivonva)  
10: Motor jobb mért erő (nullért kivonva)  
11: Raspi akkumlátor analog   
12: RAD jelenlegi mérés azonosító szám (array id)  
13: RAD jelenlegi mérés előtt -4  
14: RAD jelenlegi mérés előtt -3  
15: RAD jelenlegi mérés előtt -2  
16: RAD jelenlegi mérés előtt -1  
17: RAD legfrissebb mérés
18: -
19:  
20: Soros komm buffer size  
21: Rpi processzor hőmérséklet  
22: Dőlés x  
23: Dőlés y  
24: MPU hőmérséklet  
25: Küldés időpontja   
26: Iránytű adat



<br>

### Vezérlőegység Rpi &#8594; Fedélzeti Rpi
* TCP kommunikáció
* int Array 30 elem

0: (tapasztalatok alpján az érték nem érkezik meg megfelelően)    
1: motor2 %-os érték  
2: mélységmérés bool  
3: tápegység állapot 1(alap), 2(aruino másodlagos, rpi els.) 3(másodlagosok), 4(rpi masodlagos arduino elsodleges), 5(vészakku)  
4: ballaszttartály 1 áll. %  
5: ballaszttartály 2 áll. %  
6: hűtőventillátor %  
7: Pontonhajó kormány
8: Radar működés 
9: Motor resetelésének kérése  
10: motor1 %-os érték  
11: Raspi akkumlátor analog  
 -   *Robotkar adatfolyam*
12: Alsó motor forgató írandó érték  
13: Forgófej motor állás  
14: Alsó karmozgató  
15: Felsó karmozgató  
16: Navigációs motor PWM 1  
17: Navigációs motor PWM 1 
18: Élő kép kérés   
19: Pontonhajó motor  
20: ballaszt bal tartály   
21: ballaszt jobb tartaly   

<br>

### Fedélzeti RPi &#8594; Fedélzeti arduino
* TCP kommunikáció
* int Array 30 elem

0: -   
1: motor2 %-os érték  
2: mélységmérés bool  
3: tápegység állapot 1(alap), 2(aruino másodlagos, rpi els.) 3(másodlagosok), 4(rpi masodlagos arduino elsodleges), 5(vészakku)  
4: ballaszttartály 1 áll. %  
5: ballaszttartály 2 áll. %  
6: hűtőventillátor %  
7: -- 
8: radar on?   
9: Motor resetelésének kérése  
10: motor1 %-os érték
11:  
 -   *Robotkar adatfolyam*
12: Alsó motor forgató írandó érték  
13: Forgófej motor állás  
14: Alsó karmozgató  
15: Felsó karmozgató  


16:  
17:
18:
19:  
20:
21: Kamera kép kérése  

<br>

### A fedélzeti arduino &#8594; fedélzeti Rpi
* Soros kommunikáció
* Array 20 elem  

0: kommunikáció sikeressége  
1: belső víz magassága  
2: Mélység, hiba esetén 0, nem mért: előző érték  
3: error száma  
4: csp1 mérése  
5: Hőmérő 1 hőmérséklet (az ESC-hez!)  
6: Hőmérő 2 hőmérséklet (az ESC-hez!)  
7: Hőmérés DHT  
8: Páratartalom  
9: Motor bal mért erő (nullért kivonva)  
10: Motor jobb mért erő (nullért kivonva)  
11: -
12: -
13: -
14: -
15: -
16: -
17: -
18: -
19: -

### Vezérlőegység arduino &#8594; vezérlőegység RPi

10: bal motor
11: jobb motor


<br>
<br>

## Folyamatok
<br>  

### Parti egység
- p1: GUI - A grafikus felületet, és az UPD kommunikációt kezelő folyamat  
- p2: A TCP kommunikációt, és az onnan érkező adatok állandó frissességét biztosító folyamat  
- p3: A vezérlőegységgel soros kommunikációt, és az onnan érkező adatok állandó frissességét biztosító folyamat  
- p4: Az érkező kamerakép 10fps-ben való mentése, és az élő érkező, és kimenő információk ráírását végző folyamat  

<br>

### Fedélzeti egység

- p1: A TCP kommunikációt végző folyamat
- p2: A soros kommunikációt végző folyamat
- p3: Az élő kameraképet biztosító UPD kapcsolatot kezelő folyamat
- p4: A gyroszkóp adatainak feldolgozása, és élő biztosítását végrehajtó folyamat


<br>
<br>

## Megjegyzések
- VSCode SSH kiterjesztés Permission denied: sudo chown -R myuser /path/to/folder 
- A csomagösszeállításhoz a C:\Qt\QtIFW-4.1.1\bin\binarycreator.exe -c config/config.xml -p packages -f "AquaLab Installer - v0.7-1" parancs használandó

### Csatlakozási adatok
- A Raspberry pi hostapd jelszava: Tengeralattjaro2020  
- A Raspberry pi SSH jelszava: KerteeszDom (felhasznalo: pi)  
- Home passwd: NJk3fdstk
### Matekok  
    | \  
    |al\  
    |   \  
    |b   \ c  
    |     \  
    | .    \  
     -------  
        a
c - mért távolság 
al - elfordulási szög 90-érkező szög=al  
b - valós távolság  
a - mérőtől oldalirányú eltérés 

b = cos(al)*c  
a = sin(al)*c  


### Ballasztrendszer
- 0-100-es skálán
- Érzékenység állítható
- 10 ig növekszik a pöffök közti idő


country=HU
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
network{
    ssid="RUV-system-VE"
    psk="Tengeralattjaro2020"
    key_mgmt=WPA-PSK
}

169.254.15.251
fe80::8c51:8be8:bc0e:9d81
