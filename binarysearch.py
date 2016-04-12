import unittest

alist = []

inp = open("test.txt","r")

for line in inp.readlines():
	for i in line.split():
		alist.append(int(i))

print ("Unordered list is :",alist)

alist.sort()

print ("Sorted list is :",alist)

x = raw_input("Enter number to search")
number = int(x)

def binarysearch(alist,item):
	beg = 0
	end = len(alist)-1
	
	found = False
	while beg<=end or not found:
		mid = (beg+end)//2
		if(item==alist[mid]):
			found = True
			return mid
		elif (item > alist[mid]):
			beg = mid+1
		elif (item < alist[mid]):
			end = mid-1
	return -1
num = binarysearch(alist,number)
if num == -1:
	print ("Number not found")
else:
	print ("Number found at location :",1+num)

class Addtest(unittest.TestCase):

	 
   def test_positive_add(self):
      '''Verify that adding positive numbers works''' # Printed if test fails
      self.assertEqual(binarysearch(alist,4), 6) # Test will fail if "false" (boolean)
      self.assertEqual(binarysearch(alist,5), 2)
      #self.assertEqual(add(1,1,17), 19)
 
   # Functions beginning with "test" will be ran as a unit test.
   # @unittest.skip("demonstrating skipping") # Skip this test (Python >= 2.7)
   def test_negative_add(self):
      '''Verify that adding negative numbers works''' # Printed if test fails
      self.assertEqual(binarysearch(alist,-6), 0)

if __name__=='__main__':
   unittest.main()
		
	
