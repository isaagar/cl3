from bitstring import BitArray
from flask import Flask
from flask import request
from flask import render_template
app = Flask(__name__)

def booth(m,r,x,y):
	totalLength=x+y+1
	mA=BitArray(int=m,length=totalLength)
	A=mA<<(y+1)
	mA1=BitArray(int=-m,length=totalLength)
	S=mA1<<(y+1)
	P1=BitArray(int=r,length=y)
	P1.prepend(BitArray(int=0,length=x))
	P=P1 << (1)
	print "A : ",A.bin
	print "S : ",S.bin
	print "P : ",P.bin
	
	for i in range(1,y+1):
		if P[-2:] == '0b01':
			P=BitArray(int=P.int+A.int,length=totalLength)
		elif P[-2:] == '0b10':
			P=BitArray(int=P.int+S.int,length=totalLength)
		P=BitArray(int=(P.int >>1),length=P.len)
	P = P[:-1]	
	return P.bin,P.int


@app.route('/')
def f():
    return render_template("h.html")

@app.route('/',methods=['POST'])
def g():
    text1 = int(request.form['text1'])
    text2 = int(request.form['text2'])
    n,m=booth(text1,text2,8,8)
    return "Answer in binary: "+str(n)+"<br>Answer: "+str(m)
    
if __name__ == '__main__':
    app.run('192.168.0.103',debug=True)

