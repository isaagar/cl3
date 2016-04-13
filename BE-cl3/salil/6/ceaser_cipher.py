dict1 = {'a' : 0,'b' : 1, 'c' : 2,'d' : 3,'e' : 4,'f':5,'g':6,'h':7,'i':8,'j':9,'k':10,
         'l':11,'m':12,'n':13,'o':14,'p':15,'q':16,'r':17,'s':18,'t':19,'u':20,'v':21,
         'w':22,'x':23,'y':24,'z':25}
dict2 = {0:'a',1:'b',2:'c',3:'d',4:'e',5:'f',6:'g',7:'h',8:'i',9:'j',10:'k',11:'l',12:'m',13:'n',14:'o',15:'p',16:'q',
			17:'r',18:'s',19:'t',20:'u',21:'v',22:'w',23:'x',24:'y',25:'z'}
def encryption(plain_text,key):
	#returns the cipher text by encrypting plain_text using the key passed
	cipher_text = []
	for char in plain_text:
		if char in dict1:
			cipher_text.append(dict2[(dict1[char] + key) % 26])
		else:
			cipher_text.append(char)
	return "".join(cipher_text)
def decryption(cipher_text,key):
	#returns the plain text by decrypting cipher_text using the key passed
	plain_text = []
	for char in cipher_text:
		if char in dict1:
			plain_text.append(dict2[(dict1[char] - key) % 26])
		else:
			plain_text.append(char)
	return "".join(plain_text)


def main():
	choice = 0
	while (choice != 3):
		choice = int(input("1.Encryption\n2.Decryption\n3.Exit\nEnter an option : "))
		if choice == 1:
			plain_text = str(input("Enter the plain text : ")).lower()
			key = int(input("Enter the key(number of shifts) : "))
			print ("Plain Text : ",plain_text)
			print("Cipher Text : ",encryption(plain_text,key))

		elif choice == 2:
			cipher_text = str(input("Enter the cipher text : ")).lower()
			key = int(input("Enter the key(number of shifts) : "))
			print ("Cipher Text : ",cipher_text)
			print("PLain Text : ",decryption(cipher_text,key))

		elif choice == 3:
			print ("Bye bye...")
			break

		else:
			print ("Invalid option, try again..")

if __name__ == '__main__':
	main()


'''
output :
banty@banty:~/python/encryption algo/final algos$ python3 ceaser_cipher.py
1.Encryption
2.Decryption
3.Exit
Enter an option : 1
Enter the plain text : This is the plain text
Enter the key(number of shifts) : 3
Plain Text :  this is the plain text
Cipher Text :  wklv lv wkh sodlq whaw
1.Encryption
2.Decryption
3.Exit
Enter an option : 2
Enter the cipher text : wklv lv wkh sodlq whaw
Enter the key(number of shifts) : 3
Cipher Text :  wklv lv wkh sodlq whaw
PLain Text :  this is the plain text
1.Encryption
2.Decryption
3.Exit
Enter an option : 3
Bye bye...

'''