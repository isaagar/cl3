import sys
from xml.dom import minidom


board = []

def danger(row, col):
    for (i, j) in board:
        if row == i: return True
        if col == j: return True
        if abs(row - i) == abs(col - j): return True

    return False
    
def placequeen(row,size):
    if row > size:
        print board
	sys.exit(0)
    else:
        for col in range(1, size + 1):
            if not danger(row, col):
                board.append((row, col))
                placequeen(row + 1,size)
                board.remove((row,col))

def placequeen_multiple(row,size):
    if row > size:
        print board
    else:
        for col in range(1, size + 1):
            if not danger(row, col):
                board.append((row, col))
                placequeen_multiple(row + 1,size)
                board.remove((row,col))
		
xmldoc = minidom.parse('queens.xml')
name = xmldoc.getElementsByTagName("Q1")[0]
pos = int(name.childNodes[0].nodeValue)			
choice = input("ENTER 4 FOR 4-QUEEN OR 8 FOR 8 QUEEN PROBLEM :")
if choice == 4:
	print 
	choice_2 = raw_input("PRESS 'Y' FOR ONE SOLUTION AND 'N' FOR ALL SOLUTIONS : ")
	if choice_2 == 'Y' or choice_2 =='y':
		placequeen(pos,4)
	else :
		
		placequeen_multiple(pos,4)
elif choice == 8:
	choice_2 = raw_input("PRESS 'Y' FOR ONE SOLUTION AND 'N' FOR ALL SOLUTIONS : ")
	if choice_2 == 'Y' or choice_2 =='y':
		placequeen(pos,8)
	else :
		placequeen_multiple(pos,8)
	

