from time import time
from random import randint, seed

def GCD(n,m):
    if None == n or None == m or n <= 0  or m <= 0:
        return None
    if n < m:
        n, m = m,n
    while m > 0:
        if 0 == n % m:
            return m
        n,m = m,n%m

def test():
    test_num = 10
    mn,mx = 3, 89
    seed(time())
    for _ in range(test_num):
        n,m = randint(mn,mx), randint(mn,mx)
        print(n,m,GCD(m,n))

if __name__ == '__main__':
    test()
