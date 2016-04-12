import socket
import rand_num_gen

key = rand_num_gen.prng()
base = 71
prime = 37

K1=(base ** key)%prime

print "K1: ",K1

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host = socket.gethostname()
port = 8800
s.connect((host,port))


s.sendall(str(K1))
msg = s.recv(1024)

Mk=(int(msg) ** key)%prime
print "common key Mk: ",Mk

original = raw_input("Enter text: ")
encrypt=[]
for i in range (0,len(original)):
	encrypt.append(str(ord(original[i]) + Mk))	
print "encrypted: ",encrypt
s.sendall(" ".join(encrypt))
s.close()
