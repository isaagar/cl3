import unittest
from booth import booth
class TestBooth(unittest.TestCase):
	def test_positive(self):
		self.assertEqual(booth(3,4,8,8),10)

if __name__ == "__main__":
	unittest.main()