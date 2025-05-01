# Tengeralattjaro-cpp

This repository is part of the old software development for the submarine project.

## About the Programs

The entire project will be made open-source, and making this repository public is the first step in that process.

If you have any questions regarding the code, feel free to ask them in the [Issues](https://gitlab.com/krtdm/tengeralattjaro-cpp/-/issues) section or via email.

### Website

The project's website was [aqualab.hu](https://www.aqualab.hu), which I also developed, although it is currently inactive.

### Repository Structure

- The `src-py` folder contains the Python program that runs on the onboard Raspberry Pi. It handles communication with the onboard Arduino and the control unit, as well as collecting certain data via I2C.

- The `src-cpp` folder contains the C++ code, structured as follows:
  - The `arduino` subfolder holds the firmware for the onboard Arduino and the hardware part of the control unit.
  - The `vezerloegyseg-gui` folder contains a precompiled graphical control program. It manages communication, controls, and displays incoming data. The GUI is built using the Qt framework and can display `.al` dive log files included in the example package.
  - The `megrendeloi-gui` folder is under development and contains the files for a simplified, user-friendly version of the GUI intended for clients. This version is planned to be public.
  - Although primarily written in C++, some Python scripts are also found in the `cpp` directory. These are embedded in the GUI to handle certain communication tasks that were not practical to implement in C++ due to language limitations.

# Versions
The project require Qt 5.12.5 framework.



# Tengeralattjaro-cpp

A tengeralattjáró projekt szoftveres hátterének fejlesztése zajlott itt.

# A programokról
A teljes projektet nyílt forráskódúvá fogom tenni, ezen repo nyilvánosságra hozása az első lépés ebben.

Amennyiben kérdésük van a kódokkal kapcsolatban az [Issues](https://gitlab.com/krtdm/tengeralattjaro-cpp/-/issues) menüben, vagy emailban tudják feltenni.

### Honlap
A projekt honlapja az [aqualab.hu](https://www.aqualab.hu), ezt szintén én fejlesztettem ki, azonban már inaktív.


### A repo felépítése
Az src-py mappában található a fedélzeti Raspberry Pi számítógépen futó python program található. Ez a fedélzeti arduino-val, és a vezérlőegységgel történő kommunikációért, és bizonyos adatok (I2C) adatok begyűjtéséért felelős.  
Az src-cpp mappában találhatók a C++ nyelven írt kódok, melyek az alábbiak:  
- Az aruduino mappában a fedélzeten futó kód, és a vezérlőegység hardveres részének kódja található
- A vezerloegyseg-gui mappában található a lefordítva is nyilvánosságra hozott program, mely a kommunikációt, a vezérlést, és a beérkező adatok megjelenítésést végzi. A grafikus felület a Qt keretrendszert használja, és képes a mintaként a fordított csomagba mellékelt .al merülési naplók megjelenítésére. 
- A megrendeloi-gui mappábana  jelenleg még fejlesztés alatt álló, megrendelőknek készülő, némileg letisztultabbra, könnyebben kezelhetőre, és nyilvánosra tervezett projekt fájljai találhatóak.
- A cpp mappában is megtalálhatók néhol python programok, ezek a GUI felületbe ágyazva végeznek el bizonyos kommunikációs feladatokat, melyeket a C++ sajátosságai miatt nem volt érdemes átírni.


