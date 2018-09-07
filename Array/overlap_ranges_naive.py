from random import seed,randint
from time import time
from collections import Counter

def overlap_ranges_naive(ranges):
    if None ==ranges or 0 == len(ranges):
        return 0
    st=[0]*(1+max([r[1] for r in ranges]))
    cnt = 0
    for r in ranges:
        cnt += 1
        for i in range(r[0],r[1]+1):
            st[i] = cnt
    print('st:',st)
    cnt = Counter(st)
    keys=cnt.keys()
    num = len(keys)
    if 0 in keys: num -= 1
    return num

def test():
    ln = 10
    mn,mx=1,23
    seed(time())
    ranges=[]
    print('ranges:')
    for i in range(ln):
        l = randint(mn,mx-1)
        h = randint(l,mx)
        r=(l,h)
        ranges.append(r)
        print(i+1,r)
    num = overlap_ranges_naive(ranges)
    print('num:', num)

if __name__=='__main__':
    test()