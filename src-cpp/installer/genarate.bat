

set /p id="Enter ID: "

copy "..\build-vezerlo-gui-Desktop_Qt_5_15_2_MinGW_64_bit-Release\vezerlo-gui.exe" ".\packages\com.vezerlo\data"


windeployqt ".\packages\com.vezerlo\data\vezerlo-gui.exe"
"C:\Qt\Tools\QtInstallerFramework\4.3\bin\binarycreator.exe" -c config/config.xml -p packages -f "AquaLab Installer - v0.9-%id%"

set /p exit="Exit"