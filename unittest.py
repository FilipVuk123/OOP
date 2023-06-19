import unittest
from unittest import TestCase

class Samoglasnici(object):
    def __init__(self, w):
        self.word = w
        
    def daj_samoglasnike(self):
        s = ""
        for i in self.word:
            if i in "aeiou":
                s += i
        return str(s)
      
class TestSamoglasnici(TestCase):
    words = [("fil...ip", "ii"), ("riba", "ia"), ("Le..a","ea")]
    
    def test_samoglasnici(self):
        for test in self.__class__.words:
            rijec = Samoglasnici(test[0])
            real = rijec.daj_samoglasnike()
            expected = test[1]
            self.assertEqual(real, expected)

if __name__== "__main__":
    unittest.main()