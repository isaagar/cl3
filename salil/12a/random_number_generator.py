import random
import datetime,time
def prng():
	a = random.randint(200000,500000)					#random.randint(x,y) generates a random no b/w x & y. 
	b = random.randint(500000,900000)
	c = random.randint(2000,500000)

	seed = int(time.mktime(datetime.datetime(2011,10,21,0,0).timetuple()))	#taking system time as random number
										#any other function can also be used in its place.
	seed = a * seed + b
	seed = seed % c
	return seed
