dict1 = {'a':0,'b':1,'c':2,'d':3,'e':4,'f':5,'g':6,'h':7,'i':8,'j':9,'k':10,'l':11,'m':12,'n':13,'o':14,'p':15,'q':16,'r':17,'s':18,'t':19,'u':20,'v':21,'w':22,'x':23,'y':24,'z':25}

dict2 = {0:'a',1:'b',2:'c',3:'d',4:'e',5:'f',6:'g',7:'h',8:'i',9:'j',10:'k',11:'l',12:'m',13:'n',14:'o',15:'p',16:'q',17:'r',18:'s',19:'t',20:'u',21:'v',22:'w',23:'x',24:'y',25:'z'}

def encrypt(plain,key):
	cipher = []
	for char in plain:
		if char in dict1:
			cipher.append(dict2[(dict1[char]+key)%26])
		else:
			cipher.append(char)
	return "".join(cipher)

def decrypt(cipher,key):
	plain = []
	for char in cipher:
		if char in dict1:
			plain.append(dict2[(dict1[char]-key)%26])
		else:
			plain.append(char)
	return "".join(plain)


def main():
	choice=0
	while choice!=3:
		choice=int(input("1. encrypt 2.decrypt 3.exit"))
		if choice==1:
			plain=str(input("Enter plain").lower())
			key = int(input("enter key"))
			print ("plain text: ",plain)
			cipher=encrypt(plain,key)
			print ("cipher text: ",cipher)
		elif choice==2:
			cipher=str(input("Enter cipher").lower())
			key = int(input("enter key"))
			print ("cipher text: ",cipher)
			plain=decrypt(cipher,key)
			print ("plain text: ",plain)
		elif choice==3:
			print ("exiting")
			break
		else:
			print("Invalid OP")

if __name__=='__main__':
	main()

