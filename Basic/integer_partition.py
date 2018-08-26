from random import seed,randint
from time import time

def f(n,m):
    if n ==1 or m == 1:
        return 1
    if n < m:
        return f(n,n)
    if n == m:
        return 1 + f(n,n-1)
    if n > m:
        return f(n,m-1) + f(n-m,m)
def test():
    mn,mx = 2,13
    seed(time())
    n,m = randint(mn,mx),randint(mn,mx)
    cnt = f(n,m)
    print(n,m,cnt)

if __name__ == '__main__':
    test()