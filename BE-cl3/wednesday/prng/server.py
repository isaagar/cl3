import socket
import random_number_generator				#importing file containing PRNG code

server_key=random_number_generator.prng()		#generation of random number using PRNG Function
print "Server's Random Number (X) :",server_key

#Generating Key K1 for Diffy-Hellman Key Exchange
shared_base=2583
shared_prime=89827481
K1 = (shared_base ** server_key) % shared_prime
print "K1=",K1

#Establishing Server
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM,socket.IPPROTO_TCP)
host = socket.gethostname() 
port = 12001
s.bind((host,port))
s.listen(3)              
new_s, addr=s.accept()


msg=new_s.recv(200)					#Recieving K2 from client in 'msg'
print "K2 as recieved from client:",msg

new_s.send(str(K1))					#Sending K1 to Client


Mkey = (int(msg) ** server_key) % shared_prime		#computing common key using K2 & K1
print "Common Key generated using K1 & K2:",Mkey


###########CODE BELOW IS JUST TO DEMONSTRATE CRYPTOGRAPHY WITH EXAMPLE##########
###ENCODED MESSAGE IS RECIEVED FROM CLIENT, THEN ITS DECRYPTED AND DISPLAYED####

enc_msg=new_s.recv(1024)				#Recieving Encoded Message from CLEINT
x = [int(i) for i in enc_msg.split()]			#converting Recieved String into List for decoding
							#split() function is used for this purpose
print "Recieved Encoded Message: ",x

#Decoding Encrypted Message
dec_msg =[]
for j in range (0,len(x)):
	dec_msg.append(chr(x[j] - Mkey))		#CHR converts datatype to character
							#append adds next value at the end

print "Decrypted Message=","".join(dec_msg)		#printing list as string

s.close()						#close connection
new_s.close()						#close server
