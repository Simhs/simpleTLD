import socket
import sys
import thread
import os

class Tracker:
    def __init__(self):
	self.mode = 1
        thread.start_new_thread(self.Opentldfileopen,())
        self.tld_obj = TLDsock()

        thread.start_new_thread(self.tcploop,())
        self.command = "normal"
        self.recv_data = None

        self.startTracking = False
        self.area =(0,0,0,0)
        self.EndTracking = False
        self.closeTLD = False


    def __init__(self,mode = 0):
	self.mode = mode
        thread.start_new_thread(self.Opentldfileopen,())
        self.tld_obj = TLDsock()

        thread.start_new_thread(self.tcploop,())
        self.command = "normal"
        self.recv_data = None

        self.startTracking = False
        self.area =(0,0,0,0)
        self.EndTracking = False
        self.closeTLD = False

    def __del__(self):
        self.closeTLD = True

    def Opentldfileopen(self):
        os.system("opentld "+str(self.mode))

    def tcploop(self):
        while True:
            self.recv_data = self.tld_obj.recvData()
            if not self.recv_data:
                break
            if self.startTracking:
                self.command = "set"
                self.startTracking = False
            elif self.EndTracking:
                self.command = "clear"
                self.EndTracking = False
            elif self.closeTLD :
                self.command = "close"

            self.tld_obj.sendOperate(self.command, self.area)
            self.command = "normal"

    def tracking(self,area):
        self.area = area
        self.startTracking = True

    def clearTracking(self):
        self.EndTracking = True

    def close(self):
        self.__del__()

    def getData(self):
	
	if self.recv_data == None:
		return ('0000','0000','0000','0000')
        splitlsit = str(self.recv_data).split('/')
        x1 = splitlsit[1]
        y1 = splitlsit[2]
        x2 = splitlsit[3]
        y2 = splitlsit[4]
        return (x1,y1,x2,y2)


class TLDsock:
    def __init__(self):
        self.ltx = 0
        self.lty = 0
        self.rbx = 0
        self.rby = 0
        self.sock = None
        self.connection = None
        self.client_address = None
        self.bind()
        self.acceptClient()

    def bind(self):
        # Create a TCP/IP socket
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Bind the socket to the port
        server_address = ('localhost', 10000)
        print >>sys.stderr, 'starting up on %s port %s' % server_address
        self.sock.bind(server_address)
        # Listen for incoming connections
        self.sock.listen(1)
        print >> sys.stderr, 'waiting for a connection'

    def acceptClient(self):
        self.connection, self.client_address = self.sock.accept()


    def sendOperate(self,op_str,area):
        if op_str == "normal":
            msg = "0000/0000/0000/0000/0000"
        elif op_str == "set":
            msg = "1111/" + str(area[0]).zfill(4) + "/" + str(area[1]).zfill(4) + "/" + str(area[2]).zfill(4) + "/" + str(area[3]).zfill(4)
        elif op_str == "clear":
            msg = "2222/0000/0000/0000/0000"
        elif op_str == "close":
            msg = "3333/0000/0000/0000/0000"
        else:
            raise ValueError('A very specific bad thing happened')
        self.connection.sendall(msg)


    def recvData(self):
        data = self.connection.recv(25)
        if not data:
            print >> sys.stderr, 'no more data from', self.client_address
            return False
        return data





if __name__ == "__main__":
    tld = TLD(1)
    time.sleep(3)
    print tld.getData()
    tld.tracking((100,100,200,200))
    print tld.getData()
    time.sleep(5)
    tld.clearTracking()
    print tld.getData()
    time.sleep(2)
    tld.tracking((100,100,200,200))
    time.sleep(5)
    tld.clearTracking()
    time.sleep(2)
    tld.close()



