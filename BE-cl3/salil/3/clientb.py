import socket # Import socket module
# Accept input
multiplicant=raw_input("Multiplicand :")
multiplier=raw_input("Multiplier :")
s = socket.socket()
# Create a socket object
host = socket.gethostname() # Get local machine name
port = 12345
# Reserve a port for your service.
s.connect((host, port))
s.send(multiplicant)
print s.recv(1024)
s.send(multiplier)
print s.recv(1024)
s.send("From client: Do the calculations for me")
b=s.recv(1024)
print("Answer: " + b)
s.close
