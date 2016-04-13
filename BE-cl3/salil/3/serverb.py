#!/usr/bin/python
from bitstring import BitArray
import socket



def booth(m,r,x,y):
	totalLength=x+y+1
	mA=BitArray(int=m,length=totalLength)
	rA=BitArray(int=r,length=totalLength)
	A=mA<<(y+1)
	S=BitArray(int=-m,length=totalLength)<<(y+1)
	P=BitArray(int=r,length=y)
	P.prepend(BitArray(int=0,length=x))
	P=P<<1
	print "initial values"
	print "A",A.bin
	print "S",S.bin
	print "P",P.bin
	print "Start calc"
	for i in range(1,y+1):
		if P[-2:]=='0b01':
			P=BitArray(int=P.int+A.int, length=totalLength)
			print "P+A=",P.bin
		elif P[-2:]=='0b10':
			P=BitArray(int=P.int+S.int, length=totalLength)
			print "P+S=",P.bin
		P=arith_shift_right(P,1)
		print "P>>1: ",P.bin
	P=arith_shift_right(P,1)
	print "P>>1: ",P.bin
	return P.int
		
def arith_shift_right(x,amt):
	l=x.len
	x=BitArray(int=(x.int>>amt),length=l)
	return x
	
s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 12345             # Reserve a port for your service.
s.bind((host,port))        # Bind to the port
s.listen(5)  
while True:
	c, addr=s.accept()
	print "Established....",addr
	m=c.recv(1024)
	print "m: ",m
	c.send('m recvd')
	r=c.recv(1024)
	print "r: ",r
	c.send('r recvd')
	b=booth(int(m),int(r),8,8)
	print "answer", b
	c.send(str(b))
	c.close()	
	
