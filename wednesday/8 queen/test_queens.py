from eight_queens import solution
import unittest

class TestEightQueens(unittest.TestCase):
	def test_solution(self):
		self.assertEqual(solution(),[(4, 1), (7, 2), (5, 3), (2, 4), (6, 5), (1, 6), (3, 7)])

if __name__ == "__main__":
	unittest.main()