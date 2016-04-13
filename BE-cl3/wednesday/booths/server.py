import socket
import booth

s = socket.socket()
host = socket.gethostname()
port = 1111
s.bind((host,port))
s.listen(5)

while True:
	c , addr = s.accept()
	print("Connected with client ",addr)
	multiplicand = c.recv(200)
	print("Recieved %d Multiplicand from client"%int(multiplicand))
	c.send("Multiplicand received")
	multiplier = c.recv(200)
	print("Recieved %d Multiplier from client"%int(multiplier))
	c.send("Multiplier received")
	b = booth.booth_multiplication(int(multiplicand),int(multiplier),8,8)
	c.send(str(b))

s.close()
