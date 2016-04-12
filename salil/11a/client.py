# client.py  with TKinter
import socket
import sha1
from Tkinter import *

mess=""
message=""

def Server():
	mess=E1.get()
	s.send(mess)
def fromServer():
	message = s.recv(4096)
	mparts=message.split("#")
	newSha1=sha1.sha1(mparts[0])

	if mparts[1] <> newSha1 :
	
	
		L2 = Label(top, text="Message has been tampered and hash value is")
		L2.pack( side = LEFT)
	
	
	else:	
		
		L2 = Label(top, text="Message successfully received and authenticated and hash value is"+mparts[1])
		L2.pack( side = LEFT)
		print "Message successfully received and authenticated",mparts[1]
	
	
   
# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# get local machine name
host = socket.gethostname()                           

port = 9998
# connection to hostname on the port.
s.connect((host, port))                               

top = Tk()

L1 = Label(top, text="Enter the request")
L1.pack(side = LEFT)

E1 = Entry(top, bd =5)
B1 = Button(top, text ="Send to server",command=Server)
B1.pack()
E1.pack()
B2 = Button(top, text ="Receive from server",command=fromServer)
B2.pack()

                                   
top.mainloop()
s.close()
