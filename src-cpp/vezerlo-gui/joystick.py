import pygame
import time
import sys
import os

file_path = os.path.realpath(__file__)

try:
    pygame.init()
    pygame.joystick.init()
    j=pygame.joystick.Joystick(0)
    j.init()
    jo=1
    pygame.event.get()
    time.sleep(.1)
    joyyNull=j.get_axis(0)
    joyxNull=j.get_axis(1)
    joyzNull=j.get_axis(3)
    # prl('Joystick érzékelve',1)
except:
    print("Joystick nem található ",sys.exc_info())
    jo=0


while jo==1:
    try:
        pygame.event.get()
        txt=str(j.get_axis(0))+' '+str(j.get_axis(1))+' '+str(j.get_axis(3))+' '+str(j.get_button(0))+' '+str(j.get_button(1))+' '+str(j.get_button(2))+' '+str(j.get_button(3))+' '+str(j.get_button(4))+' '+str(j.get_button(5))+' '+str(j.get_button(6))+' '+str(j.get_button(7))+' '+str(j.get_button(8))+' '+str(j.get_button(9))+' '+str(j.get_button(10))+' '+str(j.get_button(11))
        f=open(file_path.replace("joystick.py","joystick.txt"),'w')
        f.write(txt)
        f.close()
    except KeyboardInterrupt:
        print("Kilépés: KeyboardInterrupt")
        f.close()
        break
    except:
        print("Kilépés: Ismeretlen: ", sys.exc_info())
        f.close()
        break






