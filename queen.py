import json
inf=open("8q.json")
board=json.loads(inf.read())
board=board['matrix']
count =1

def issafe(row,col,matrix,n):
	for i in range (n):
		for j in range (n):
			if matrix[i][j]==1:
				if row==i:
					return False
				elif col==j:
					return False
				elif abs(row-i)==abs(col-j):
					return False
	return True
	
def solution(matrix,n,col):
	global count
	if count>=n:
		return True
	
	for i in range (n):
		if issafe(i,col,matrix,n):
			matrix[i][col]=1
			count+=1
			if solution(matrix,n,(col+1)%n)==True:
				return True
			matrix[i][col]=0
			count-=1
	return False
	
def main(n):
	global count
	count=1
	matrix=[[0]*8 for i in range(8)]
	for i in range(8):
		for j in range(8):
			if board[i][j]==1:
				row=i
				col=j
	matrix[row][col]=1
	
	if solution(matrix,n,(col+1)%8)==True:
		print matrix
	else:
		print "No Solution"
	
main(8)	
