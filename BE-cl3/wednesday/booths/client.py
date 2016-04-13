import socket

m = raw_input("\nEnter Multiplicand : ")
r = raw_input("\nEnter Multiplier : ")

s = socket.socket()
host = socket.gethostname()
port = 1111
s.connect((host,port))

s.send(m)
print s.recv(200)
s.send(r)
print s.recv(200)
b = s.recv(200)
print "Answer = ",b
s.close()

