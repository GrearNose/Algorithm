from random import seed, randint
from time import time

def sum_cnt(addens,occ=None):
    """
        Given a set of addens, figure out their how many different sum they can
        sum up to.
        === Args ===
        addens: the set of addens to add;
        occ: the occrance of each adden in addens.
        return: the number of the different sums, the set of sums.
    """
    if None == addens or 0 == len(addens):
        return 0
    if None == occ:
        occ = [1]*len(addens)
    sums = set([0])
    for i in range(len(addens)):
        trials = [addens[i]*t+s for t in range(1,occ[i]+1) for s in sums]
        sums.update(trials)
    return len(sums),sums

def test():
    test_num = 10
    test_ln = 5
    mn,mx = 2,5
    for _ in range(test_num):
        addens = [randint(mn,mx) for _ in range(test_ln)]
        print(addens, sum_cnt(addens))

if __name__ == '__main__':
    test()

