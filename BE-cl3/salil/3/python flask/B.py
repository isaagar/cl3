from bitstring import BitArray
from flask import Flask
from flask import request
from flask import render_template
app = Flask(__name__)

def booth(m,r,x,y):
	totalLength = x + y + 1
	A = BitArray(int = m , length = totalLength ) << (y+1)
#	rA = BitArray(int = r , length = totalLength )
#	A = mA  <<  (y+1)
	S = BitArray(int = -m , length = totalLength ) << (y+1)
	P = BitArray(int = r , length = y )
	P.prepend(BitArray(int = 0 , length = x))
	P = P << 1
	# "Initial values : "
	print "A = ",A.bin
	print "S = ",S.bin
	print "P = ",P.bin
	for i in range(1,y+1):
		if P[-2:] == "0b01" :
			P = BitArray(int = P.int + A.int , length = totalLength)
			print "P + A :",P.bin
		elif P[-2:] == "0b10" :
			P = BitArray(int = P.int + S.int , length = totalLength)
			print "P + S :",P.bin
		P = arith_shift_right(P,1)
		print "P >> 1 ",P.bin
	P = arith_shift_right(P,1)
	print "P >> 1 :",P.bin
	print "Integer :",P.int
	return P.bin,P.int

def arith_shift_right(x,amt):
	l = x.len
	x = BitArray(int =(x.int >> amt) , length = l)
	return x

@app.route('/')
def f():
	return render_template("h.html")

@app.route('/',methods=['POST'])
def g():
	text1 = int(request.form['text1'])
	text2 = int(request.form['text2'])
	n,m = booth(text1,text2,4,4)
	return "Answer in binary : "+str(n)+"<br>Answer in Integer: "+str(m)
if __name__ == '__main__':
	app.run('localhost',debug=True)
