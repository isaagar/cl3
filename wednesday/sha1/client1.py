# client1.py without tkinter  
import socket
import sha1

# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# get local machine name
host = socket.gethostname()                           

port = 9998
# connection to hostname on the port.
s.connect((host, port))                               
# Receive no more than 1024 bytes
mess=raw_input("Enter the request")
s.send(mess)
message=""
message = s.recv(4096)
mparts=message.split("#")
newSha1=sha1.sha1(mparts[0])

if mparts[1] <> newSha1 :
	print "Message tampered",mparts[1]
	
else:
	print "Message successfully received and authenticated",mparts[1] 
s.close()
                   

