import socket
import rand_num_gen

key = rand_num_gen.prng()
base = 71
prime = 37

K2=(base ** key)%prime

print "K1: ",K2

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host = socket.gethostname()
port = 8800
s.bind((host,port))
s.listen(5)

new,addr=s.accept()
msg = new.recv(1024)
new.sendall(str(K2))
Mk=(int(msg) ** key)%prime
print "common key Mk: ",Mk
decrypt=[]
encrypt = new.recv(1024)
x = [int(i) for i in encrypt.split()]
print "encrypted: ",x
#for i in range(0,len(encrypt)):
#	decrypt.apppend(str(ord(encrypt[i])-Mk))
dec_msg =[]
for j in range (0,len(x)):
	dec_msg.append(chr(x[j] - Mk))
print "decrypted: ","".join(dec_msg)
new.close()

