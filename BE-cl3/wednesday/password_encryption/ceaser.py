dict1 = {'a':0 , 'b':1, 'c':2, 'd':3, 'e':4, 'f':5, 'g':6, 'h':7, 'i':8, 'j':9, 'k':10, 'l':11, 'm':12, 'n':13, 'o':14, 'p':15, 'q':16, 'r':17, 's':18, 't':19, 'u':20, 'v':21 , 'w':22 , 'x':23 , 'y':24, 'z':25}
dict2 = {0:'a' , 1:'b' , 2:'c', 3:'d' , 4:'e' , 5:'f', 6:'g', 7:'h' , 8:'i' , 9:'j' , 10:'k' , 11:'l' , 12:'m' , 13:'n' , 14:'o' , 15:'p' , 16:'q' , 17:'r', 18:'s' , 19:'t' ,20:'u' , 21:'v' , 22:'w' , 23:'x' , 24:'y' , 25:'z' }

def encryption(plain_text,key):
  cipher_text = []
  for char in plain_text:
    if char in dict1:
      cipher_text.append(dict2[(dict1[char] + key) % 26])
    else:
      cipher_text.append(char)
  return "".join(cipher_text)

def decryption(cipher_text,key):
  plain_text = []
  for char in cipher_text:
    if char in dict1:
      plain_text.append(dict2[(dict1[char] - key) % 26])
    else:
      plain_text.append(char)
  return "".join(plain_text)

def main():
  choice = 0
  while(choice != 3):
    print("\n1.Encryption\n2.Decryption\n3.Exit")
    choice = int(input("\nEnter the choice: "))
    if choice == 1 :
       plain_text = str(input("\nEnter the plain text :")).lower()
       key = int(input("\nEnter the key : "))
       print("\nCipher text :",encryption(plain_text,key))
    elif choice == 2:
       cipher_text = str(input("\nEnter the cipher text : ")).lower()
       key = int(input("\nEnter the key : "))
       print("\n Plain text :",decryption(cipher_text,key))
    elif choice == 3 :
       print("Exiting")
    else :
        print("\n Invalid selection, try again")

if __name__ == '__main__':
  main()
