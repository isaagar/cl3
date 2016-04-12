import threading
import xml.etree.ElementTree as X
def part(arr,low,high):
	p,i=arr[high],low
	for j in range(low,high):
		if arr[j]<=p:
			arr[i],arr[j]=arr[j],arr[i]
			i+=1
	arr[i],arr[high]=arr[high],arr[i]
	return i
def qsort(arr,low,high):
	if low<high:
		p=part(arr,low,high)
		t1=threading.Thread(target=qsort,args=(arr,p+1,high))
		t2=threading.Thread(target=qsort,args=(arr,low,p-1))
		t1.start()
		t2.start()
		t1.join()
		t2.join()
r=X.parse("input.xml").getroot()
arr=map(int,r.text.split())
qsort(arr,0,len(arr)-1)
for i in arr:
	print i
