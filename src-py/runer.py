from __future__ import division

import os
import multiprocessing
from multiprocessing import Array, Value
import inspect
import signal

import ast
import socket
import base64
import numpy as np
import time
from gpiozero import CPUTemperature as cpu
	
import math	
import serial
from struct import * 
import struct
import sys
import ast
import time
import cv2
nulltime=time.time()
import smbus			#import SMBus module of I2C

def pre(txt):
    print("[Fedelzet] - [",inspect.stack()[1][3], "] - [Error] - ",txt)

def prl(txt,kiiras=0):
    if (kiiras==1): print("[Fedelzet] - [",inspect.stack()[1][3] ,"] - [Log  ] - ",txt)




def udp(serw_u,serr_u,gyro_u, udp_readed_u,bdatas_u):#kamera
    maxImg=100
    class FrameSegment(object):
        """ 
        Object to break down image frame segment
        if the size of image exceed maximum datagram size 
        """
        MAX_DGRAM = 2**16
        MAX_IMAGE_DGRAM = MAX_DGRAM - 64 # extract 64 bytes in case UDP frame overflown
        def __init__(self, sock, port, addr="192.168.31.242"): #cél ip
            self.s = sock
            self.port = port
            self.addr = addr

        def udp_frame(self, img):
            """
            Compress image and Break down
            into data segments 
            """
            img2=cv2.resize(img,(448,336))
            compress_img = cv2.imencode('.jpg', img2)[1]
            dat = compress_img.tobytes()
            size = len(dat)
            count = math.ceil(size/(self.MAX_IMAGE_DGRAM))
            array_pos_start = 0
            while count:
                array_pos_end = min(size, array_pos_start + self.MAX_IMAGE_DGRAM)
                self.s.sendto(struct.pack("B", count) +
                    dat[array_pos_start:array_pos_end], 
                    (self.addr, self.port)
                    )
                array_pos_start = array_pos_end
                count -= 1

    def saveFrame(f,s):
        pass#cv2.imwrite('./pics/p'+str(s)+'.jpg',f)

    def saveVid():
        img_array = []
        i=0
        prl('Save as photos in .mp4\n\n\n',1)
        filename='./pics/p0.jpg'
        img = cv2.imread(filename)
        height, width, layers = img.shape
        size = (width,height)
        out = cv2.VideoWriter('vid.mp4',cv2.VideoWriter_fourcc(*'FMP4'), 15, size)

        while i<maxImg:
            filename='./pics/p'+str(i)+'.jpg'
            img = cv2.imread(filename)
            img_array.append(img)
            out.write(img)
            i=i+1
        
        out.release()
        
        
    def camopen():
        i=0
        while i<6:
            cap = cv2.VideoCapture(i)
            i=i+1
            if cap.isOpened():
                prl("Sikeres kamera nyitás",1)
                return cap
                break
        if cap.isOpened()==0:
            pre("Hiba a kamera nyitásánál")
        return cap

    def main():
        """ Top level main function """
        # Set up UDP socket
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        port = 5556

        fs = FrameSegment(s, port)
        #indexelés, for, próbálgat cap.isOpened() al
        print("UDP-readed",udp_readed_u[:])
        cap=cv2.VideoCapture(10)
        try:
            while True:
                if udp_readed_u[18]==1 and cap.isOpened()==0:
                    print('Kamera kezdés')
                    cap=camopen()
                if udp_readed_u[18]==0 and cap.isOpened()==1:
                    print('Kamera befejezés')
                    cap.release()
                    while udp_readed_u[18]==0: 
                        if udp_readed_u[18]==1: break

                i=0
                while (cap.isOpened()) and udp_readed_u[18]==1:
                    _, frame = cap.read()
                    fs.udp_frame(frame)
                    if gyro_u[3]==1:
                        # saveFrame(frame,i)
                        if i>maxImg:
                        # saveVid()
                            i=0
                    uot=10 if udp_readed_u[26]==0 else udp_readed_u[26] #zero division error javítás
                    time.sleep(1/uot)
                    i=i+1
                cap.release()
        except KeyboardInterrupt:
            pre('KeyboardInterrupt - kilépés')
        except:
            pre('Ismeretlen hiba: '+str(sys.exc_info()))

        cap.release()
        cv2.destroyAllWindows()
        s.close()
    main()
    


def ser(serw_s, serr_s,gyro_s, udp_s,bdatas_s):
    def save(la):
        while len(la)<30:
            la.append(0)
        try:
            i=0
            while i<30:
                serr_s[i]=int(la[i])
                i=i+1
        except:
            pre('Adatmentés siekrtelen'+str(sys.exc_info()))

    try:
        #ser=serial.Serial(baudrate='115200', timeout=.1, port='com8')#Windows
        ser=serial.Serial(timeout=.15, port='/dev/ttyUSB0', baudrate='115200')#linux
        prl('Sikeres port nyitás',1)
        ena=1
    except:
        pre('Port nyitás sikertelen'+str(sys.exc_info()))
        ena=0

    time.sleep(3)
    ures=0
    e=0
    li=[0,0,0,0,0,0,0,0,0,0,0,0,0,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    while ena==1 and e==0:
        try:
            li[:]=udp_s[:]
            #time.sleep(.0004)
            # prl('Küldendő adat:'+str(l),1)
            # print(li)
            if len(li)<30:
                i=len(li)
                while i<31:
                    li.append(0)
                    i=i+1
            ser.write(pack ('30h',li[0],li[1],li[2],li[3],li[4],li[5],li[6],li[7],li[8],li[9],li[10],li[11],li[12],li[13],li[14], \
            li[15],li[16],li[17],li[18],li[19],li[20],li[21],li[22],li[23],li[24],li[25],li[26],li[27],li[28],li[29]))
            time.sleep(.02) 
            dat=ser.readline()
            if dat!=b''and dat!=b'\r\n':
                try:
                    ures=0
                    dats=str(dat)
                    
                    if dat!=b'0\r\n':
                        dat1=dats.replace("b","")
                        dat2=dat1.replace("'",'')
                        dat3=dat2[:-4]
                        dat3=dat3.replace('NAN,','0,')
                        list_=ast.literal_eval(dat3)
                    
                        list_.append(0)
                        list_.append(0)
                        list_.append(0)
                        list_.append(0)
                        list_.append(0)
                        list_[24]=ser.inWaiting()
                        # print('Soros porton olvasott adat: '+str(list_))
                        save(list_)
                    else:
                        ser.flushInput()
                        # pre('Delete input buffer - dat==')
                    
                    if ser.inWaiting()>6000:
                        ser.flushInput()
                        pre('Delete input buffer')
                        #time.sleep(.19)
                except KeyboardInterrupt:
                    pre('KeyboardInterrupt - break')
                    e=1
                    break
                except:
                    pre('Error in corvert, readed: '+str(dat)+str(sys.exc_info()))
                    ser.flushInput()
                    #time.sleep(.3)
            else:
                ures=ures+1
                prl('Üres +1',1)
                if ures>20:
                    prl('Üres több mint 3',1)
                    e=1
                    break
        except:
            pre(str(sys.exc_info())) #print error
            break



'''
    FS_SEL | Full Scale Range   | LSB Sensitivity
    -------+--------------------+----------------
    0      | +/- 250 degrees/s  | 131 LSB/deg/s
    1      | +/- 500 degrees/s  | 65.5 LSB/deg/s
    2      | +/- 1000 degrees/s | 32.8 LSB/deg/s
    3      | +/- 2000 degrees/s | 16.4 LSB/deg/s
    '''

def gy(serw_g,serr_g,gyro_g, udp_g,bdatas_g):
    PWR_MGMT_1   = 0x6B
    SMPLRT_DIV   = 0x19
    CONFIG       = 0x1A
    GYRO_CONFIG  = 0x1B #FS_SEL
    ACCEL_CONFIG = 0x1C
    INT_ENABLE   = 0x38
    ACCEL_XOUT_H = 0x3B
    ACCEL_YOUT_H = 0x3D
    ACCEL_ZOUT_H = 0x3F
    GYRO_XOUT_H  = 0x43
    GYRO_YOUT_H  = 0x45
    GYRO_ZOUT_H  = 0x47
    TEMP_OUT     = 0x41

    #Compass
    Register_A     = 0            
    Register_B     = 0x01           
    Register_mode  = 0x02           

    X_axis_H    = 0x03              
    Z_axis_H    = 0x05
    Y_axis_H    = 0x07
    declination = -0.00669          
    pi          = 3.14159265359     

    errlist=[0]
    #devices address
    MPU_Address = 0x68 
    GY_Address  = 0x1E
   

    def calc(ax,ay,az,T): # az itteni számításokat a csillagászatos füzet utolsó oldalán végeztem
        if ax==0 or ay==0 or az==0 or T==0:
            return
        zxc=math.sqrt(az**2+ax**2) #nyers gyorsulás adatok (ax;ay;az)
        dx=math.degrees(math.asin(az/zxc))

        zyc=math.sqrt(az**2+ay**2)
        dy=math.degrees(math.asin(az/zyc))

        dx=-dx if ax<0 else dx
        dy=-dy if ay<0 else dy

        dx=dx
        dy=dy
        T = T/340 + 16.53
        # 9.764782243012776 - 1700-as oaztás esetén az átlag g
        gyro_g[0]=dx
        gyro_g[1]=dy
        gyro_g[2]=T

    def calcCom():
        #Read Accelerometer raw value
        x = read_raw_data_gy(X_axis_H)
        z = read_raw_data_gy(Z_axis_H)
        y = read_raw_data_gy(Y_axis_H)

        heading = math.atan2(y, x) + declination
        
        #Due to declination check for >360 degree
        if(heading > 2*pi):
                heading = heading - 2*pi

        #check for sign
        if(heading < 0):
                heading = heading + 2*pi

        #convert into angle
        heading_angle = int(heading * 180/pi)
        return heading_angle

    def Magnetometer_Init():
        bus.write_byte_data(GY_Address, Register_A, 0x70)
        bus.write_byte_data(GY_Address, Register_B, 0xa0)
        bus.write_byte_data(GY_Address, Register_mode, 0)
	
    def MPU_Init():
        bus.write_byte_data(MPU_Address, SMPLRT_DIV, 7)
        bus.write_byte_data(MPU_Address, PWR_MGMT_1, 1)
        bus.write_byte_data(MPU_Address, CONFIG, 0)
        bus.write_byte_data(MPU_Address, GYRO_CONFIG, 24)
        bus.write_byte_data(MPU_Address, ACCEL_CONFIG, 1)
        bus.write_byte_data(MPU_Address, INT_ENABLE, 1)

    def read_raw_data(addr): 
        high = bus.read_byte_data(MPU_Address, addr)
        low = bus.read_byte_data(MPU_Address, addr+1)
        value = ((high << 8) | low)
        if(value > 32768):
            value = value - 65536
        return value

    

    def read_raw_data_gy(addr):
        high = bus.read_byte_data(GY_Address, addr)
        low = bus.read_byte_data(GY_Address, addr+1)
        value = ((high << 8) | low)
        if(value > 32768):
            value = value - 65536
        return value
    
    ex=0
    while ex==0:
        try:
            prl('I2C kezdés',1)
            bus = smbus.SMBus(1) 	

            MPU_Init()
            Magnetometer_Init()

            timer=0
            Gx=0
            Gy=0
            Gz=0
        except KeyboardInterrupt:
            ex=1
            break
        except OSError:
            # pre("I/O error")
            time.sleep(.1)
        except:
            time.sleep(.1)

        while True:
            timer=0.01
            try:
                acc_x = read_raw_data(ACCEL_XOUT_H)
                acc_y = read_raw_data(ACCEL_YOUT_H)
                acc_z = read_raw_data(ACCEL_ZOUT_H)
                gyro_x = read_raw_data(GYRO_XOUT_H)
                gyro_y = read_raw_data(GYRO_YOUT_H)
                gyro_z = read_raw_data(GYRO_ZOUT_H)
                temp=read_raw_data(TEMP_OUT)
                gyro_g[3]=calcCom()
            except OSError:
                # pre('MPU6050 csatlakozóhiba')
                errlist.append(4)
                serr_g[3]=4
                break
            except KeyboardInterrupt:
                ex=1
                break
            
            except:
                pre('Ismeretlen hiba')
                errlist.append(5)
                serr_g[3]=5
                break
            Ax = acc_x/2048.0
            Ay = acc_y/2048.0
            Az = acc_z/2048.0

            Gx = gyro_x/131.0
            Gy = gyro_y/131.0
            Gz = gyro_z/131.0
            calc(Ax,Ay,Az,temp)
            try:
                gyro_g[3] = calcCom()
            except KeyboardInterrupt:
                ex=1
                break
            except:
                pre('Iránytű hiba'+str(sys.exc_info()))
                
            #print ("Gx=%.2f" %Gx, u'\u00b0'+ "/s", "\tGy=%.2f" %Gy, u'\u00b0'+ "/s", "\tGz=%.2f" %Gz, u'\u00b0'+ "/s", "\tAx=%.2f g" %Ax, "\tAy=%.2f g" %Ay, "\tAz=%.2f g" %Az) 	
            #prl(str(gyro_g[:]),1)
            time.sleep(.01)

def bdat(serw_us, serr_us,gyro_us, udp_us,bdatas_b):
    cpuR=cpu()
    while True:
        try:
            bdatas_b[0]=round(cpuR.temperature,4) #21-es index
            bdatas_b[1]=round(gyro_us[0],4)
            bdatas_b[2]=round(gyro_us[1],4)
            bdatas_b[3]=round(gyro_us[2],4)
            bdatas_b[4]=round(gyro_us[3],4)
        except KeyboardInterrupt:
            pre('Kilépés')
            break
        except:
            pre('Ismeretlen hiba: '+str(sys.exc_info()))

def udp_send(serw_us, serr_us,gyro_us, udp_us,bdatas_us):
    try:
        cpuR=cpu()
        lista=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
        UDP_IP='192.168.31.242'#vevő ip címe
        UDP_PORT=6010
        udp = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        v=0
        udp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        prl("UDP kuldoegyseg OK",1)
    except:
        pre('UDP port nyitás sikertelen'+str(sys.exc_info()))
        v=1

    while v==0:
        try:
            i=0
            while i<len(serr_us):
                lista[i]=serr_us[i]
                i=i+1
            try:
                lista[25]=bdatas_us[0]
                lista[26]=bdatas_us[1]
                lista[27]=bdatas_us[2]
                lista[28]=bdatas_us[3]
                lista[29]=bdatas_us[4]
            except:
                pre("bdat error")
            irando=str(lista[:]).replace(","," ").replace("[","").replace("]","")
        except:
            pre(str(sys.exc_info())) 
        try:
            prl('UDP küldés'+str(irando))
            udp.sendto(bytes(irando, 'utf-8'), (UDP_IP, UDP_PORT))
            # print(irando)
        except:
            pre('UDP send error'+str(sys.exc_info()))
        time.sleep(0.08)

def udp_t(serw_ut, serr_ut, gyro_ut, udp_ut,bdatas_ut): #olvasás
    try:
        UDP_IP='192.168.31.247'
        UDP_PORT=6000
        MAX_DATA_SIZE=512

        udp = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP
        udp.bind((UDP_IP, UDP_PORT))
        udp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        prl("UDP olvasoegysegOK",1)
    except:
        pre('UDP olvasóegységnél hiba!'+str(sys.exc_info()))
    while True:
        try:
            data, addr = udp.recvfrom(MAX_DATA_SIZE)
            try:
                dat1=str(data)
                dat2=dat1.replace("b'","")
                dat3=dat2[:-1]
                vegso=ast.literal_eval(dat3)
#                print(vegso)
            except:
                pre('Konvertálás sikertelen'+str(sys.exc_info()))
            try:
                i=0
                if (len(vegso)<30):
                    pre("Index error: érkező adatok")
                else:
                    while i<30:
                        udp_ut[i]=int(vegso[i])
                        # serw_ut[i]=udp_ut[i]
                        i=i+1
            except:
                pre('Mentés sikertelen'+str(sys.exc_info())+str(i))
        except:
            pre('Hibás UDP adatvétel'+str(sys.exc_info()))



pids=[]
if __name__=="__main__":
    l=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    l2=[0,0,0,0,0,0,0,0,0,0,0,0,0,90,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    l3=[0,0,0,0,0]
    serr=Array('f',l2)
    serw=Array('i',l2)
    gyro=Array('f',l3) 
    udp_readed=Array('i',l2)
    bdatas=Array('f',l)
    try:
        p1 = multiprocessing.Process(target=bdat, args=(serw,serr,gyro,udp_readed,bdatas))
        p2 = multiprocessing.Process(target=ser, args=(serw,serr,gyro,udp_readed,bdatas))
        p3 = multiprocessing.Process(target=udp,args=(serw,serr,gyro,udp_readed,bdatas))
        p4 = multiprocessing.Process(target=gy, args=(serw,serr,gyro,udp_readed,bdatas))
        p5 = multiprocessing.Process(target=udp_t, args=(serw,serr,gyro,udp_readed,bdatas))
        p6 = multiprocessing.Process(target=udp_send, args=(serw,serr,gyro,udp_readed,bdatas))
        p1.start()        
        p2.start()
        p3.start()
        # p4.start()
        p5.start()
        p6.start()
        pids.append(p1.pid)
        pids.append(p2.pid)
        pids.append(p3.pid)
        # pids.append(p4.pid)
        pids.append(p5.pid)
        pids.append(p6.pid)
        p6.join()

    except:
        pre('Kilépés; hiba'+str(sys.exc_info()))

print("Kill all process")
for i in pids:
    try:
        os.kill(i, signal.SIGTERM)
    except:
        pass





