function Component(){
    print("Script 2: [OK]")
}

Component.prototype.createOperations = function()
{
    try {
        // call the base create operations function
        component.createOperations();
        // check if we are on widnows machine
        if (installer.value("os") == "win") {
            try {
                // look for user profile directory
                print("Create shortcut...");
                component.addOperation("CreateShortcut", "@TargetDir@\\vezerlo-gui.exe","@StartMenuDir@/Vezérlő felület - AquaLab.lnk",
                "workingDirectory=@TargetDir@", "iconPath=@TargetDir@\\program-icon.ico");                
                component.addOperation("CreateShortcut", "@TargetDir@\\vezerlo-gui.exe","@DesktopDir@/Vezérlő felület - AquaLab.lnk",
                "workingDirectory=@TargetDir@", "iconPath=@TargetDir@\\program-icon.ico");            
            } catch (e) {
                // Do nothing if key doesn't exist
            }
        }
    } catch (e) {
        print(e);
    }
}
