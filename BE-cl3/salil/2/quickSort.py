import threading
import xml.etree.ElementTree as X

def partiton(array, low, high):
	pivot_element = array[high]
	i = low
	
	for j in range(low, high):
		if array[j] < pivot_element:
			array[i], array[j] = array[j], array[i]
			i=i+1
	array[i],array[high] = array[high], array[i]
	return i
	
def quickSort(array, low, high):
	if low<high:
		pivot = partiton(array, low, high)
		t1 = threading.Thread(target = quickSort, args = (array, low, pivot-1))
		t2 = threading.Thread(target = quickSort, args = (array, pivot+1, high))
		t1.start()
		t2.start()
		t1.join()
		t2.join()
		
r = X.parse('input.xml').getroot()
array = map(int, r.text.split())
print("Unsorted Array -> ", array)
quickSort(array, 0, len(array)-1)
print("Sorted Array -> ",array)
