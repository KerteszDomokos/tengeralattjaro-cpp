import struct
import cv2
import pygame
import sys
import os
import multiprocessing
import numpy as np
import socket


dat=b''

def joy():
    file_path = os.path.realpath(__file__)

    try:
        pygame.init()
        pygame.joystick.init()
        j=pygame.joystick.Joystick(0)
        j.init()
        jo=1
        pygame.event.get()
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

def kep():
    MAX_DGRAM = 2**16
    global dat
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(('192.168.31.170', 5556))
    s.settimeout(5)
    dat = b''
    while True:
        seg, addr = s.recvfrom(MAX_DGRAM)
        if struct.unpack("B", seg[0:1])[0] == 1:
            # prl("finish emptying buffer",1)
            break
    # prl('Buffertörlés',1)
    def main_udp():
        """ Kép dekódolása az udp portról
        Visszatér: None """
        global dat
        seg, addr = s.recvfrom(MAX_DGRAM)
        if struct.unpack("B", seg[0:1])[0] > 1:
            dat += seg[1:]
            print ("üres")
        else:
            dat += seg[1:]
            img = cv2.imdecode(np.fromstring(dat, dtype=np.uint8), 1)
            try:
                # cv2.imshow('frame', img)
                cv2.imwrite("..\\vezerlo-gui\\live.jpg",img)
            except:
                print('megjelenítés és mentés'+str(sys.exc_info()))
                while True:
                    seg, addr = s.recvfrom(MAX_DGRAM)
                    # # prl(seg[0])
                    if struct.unpack("B", seg[0:1])[0] == 1:
                        # prl("finish emptying buffer",3)
                        break
            if cv2.waitKey(1) & 0xFF == ord('q'):
                return None
                print('None')
            dat = b''
    while True:
        main_udp()


if (__name__=="__main__"):
    p1=multiprocessing.Process(target=joy)
    p2=multiprocessing.Process(target=kep)
    p1.start()
    p2.start()
    try:
        p1.join()
        p2.join()
    except:
        p1.kill()
        p2.kill()




