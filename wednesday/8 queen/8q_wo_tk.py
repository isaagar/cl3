import json 
import Tkinter 
import time 

inf=open("8q.json") 
board=json.loads(inf.read()) 
board=board["matrix"] 

class myclass: 
	count = 1 
#To Display on terminal 
def dispboard(mat,n): 
	for i in range (0,n): 
		for j in range(0,n): 
			print(mat[i][j]), 
		print 

def issafe2(mat,row,col): 
	for i in range(8): 
		for j in range(8): 
			if(mat[i][j]==1): #if a queen exists here, then check if it attacks our queen 
				if(row==i): 
					return False 
				if(col==j): 
					return False 
				if(abs(row-i)==abs(col-j)): 
					return False 
	return True 

def solve(mat,n,col): 
	if m.count>=n: 
		return True 
	for i in range (0,n): 
		if issafe2(mat,i,col): 
			mat[i][col]=1 
			m.count +=1 
			if solve(mat,n,(col+1)%8) == True: 
				return True 
			mat[i][col]=0 
			m.count -=1 
	return False 	 

def main(n): 
	r1=0 
	c1=0 
	for i in range (0,n): 
		for j in range (0,n): 
			if (board[i][j]==1): 
				c1=j 
				r1=i 	 
	mat = [[0 for i in range (n)] for j in range(n)] 
	mat[r1][c1] = 1 
	dispboard(mat,n) 
	print("Displaying board with first queen placed..") 
	 
	if solve(mat,n,c1+1) == False: 
		print("Doesn't exist")  
	else: 
		print 
		print("Solved!")
		dispboard(mat,n) 

if __name__ == "__main__": 
	 
	m=myclass() 
	main(8)
