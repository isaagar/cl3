import random

def prng():
	seed = random.randint(1,90000)
	a=random.randint(20000,50000)
	b=random.randint(50000,90000)
	c=random.randint(5000,20000)

	seed=a*30+b
	seed=seed%c

	return seed
