alist = []
inp = open ("file","r")

for line in inp.readlines():
    
    for i in line.split():
       
        alist.append(int(i))
print "The entered list is: "
print alist

alist.sort()
print "Sorted list is : ",alist


x=input("Enter the number to be searched :")


def binarySearch(alist, item):
	    first = 0
	    last = len(alist)-1
	    found = False
	
	    while first<=last and not found:
	        midpoint = (first + last)/2
	        if alist[midpoint] == item:
	            found = True
	        else:
	            if item < alist[midpoint]:
	                last = midpoint-1
	            else:
	                first = midpoint+1
	
	    if found == True:
		return midpoint
	    else :
		return -1
	

f=(binarySearch(alist, x))
if f==-1:
	print "number not found"
else:
	print "number found at postion : ",f+1
