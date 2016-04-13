from random import randrange


def isPrime(n,k):
	if n%2==0:
		return n==2
	for i in range (1,k):
		a=randrange(2,n)
		if not isPrimestrong(n,a):
			return False
	return True
	
def isPrimestrong(n,a):
	d,s=n-1,0
	while d%2==0:
		d,s=d/2,s+1
	t=pow(a,d,n)
	if t==1:
		return True
	while s>0:
		if t==n-1:
			return True
		t=pow(t,2,n)
		s=s-1
	return False
num=input("Enter the number: ")
if (isPrime(num,4)==True):
	print "Prime"
else:
	print "Not Prime"
	
