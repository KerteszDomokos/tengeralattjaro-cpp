import socket
import time


try:
    UDP_IP='localhost' #cél IP, rpi hálózaton ált: 169.254.243.183, 169.254.198.81
    UDP_PORT=7755 #6000től 6010ig használható a ve-fedelzet kommunikációra
    udp = socket.socket(socket.AF_INET, # Internet
                    socket.SOCK_DGRAM) # UDP
    v=0
except:
    # pre('UDP port nyitás sikertelen'+str(sys.exc_info()),3)
    v=1
i=0
while v==0:
    try:
        irando="Hello from python"+str(i)
        i=i+1
    except:
        # pre(str(sys.exc_info()))
        pass
    try:
        udp.sendto(bytes(str(irando), encoding='utf-8'), (UDP_IP, UDP_PORT))
        print(irando)
    except:
        # pre('UDP send error'+str(sys.exc_info()),3)
        pass
    time.sleep(.01)
