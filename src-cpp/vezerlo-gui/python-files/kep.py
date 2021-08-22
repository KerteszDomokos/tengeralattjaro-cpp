import struct
import cv2
import sys
import os
import numpy as np
import socket

file_path = os.path.realpath(__file__)
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
            img = cv2.imdecode(np.frombuffer(dat, dtype=np.uint8), 1)
            try:
                # cv2.imshow('frame', img)
                cv2.imwrite("../vezerlo-gui/program-datas/live.jpg",img)
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

kep()