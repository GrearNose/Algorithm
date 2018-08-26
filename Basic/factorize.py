import traceback
from itertools import product
from time import time
from random import randint,seed

def primes_sifting(n):
    """
        Get all the prime numbers smaller that the given n.
    """
    if None == n or n <2:
        return None
    primes = []
    sift = [True]*(n+1)
    i = 2
    while i**2 <= n:
        for j in range(i**2,n+1,i):
            sift[j] = False
        primes.append(i)
        i += 1
        while not sift[i] and i <= n:
            i += 1
    for j in range(i,n+1):
        if sift[j]:
            primes.append(j)
    return primes

def factorize(nums):
    """
        Compute all the factors for each number in nums. The factors
        of a number is all the number that can divide it exactly, 
        including 1 and the number itself.
        e.g. the factors of 6 are: 1, 2, 3 and 6.
        === Args ===
        nums: a list of positive integer, (negative numbers are not factorized)
        return: a list of factors corresponding to each number in nums.
    """
    primes = primes_sifting(max(nums))
    primes_set = set(primes)
    facs = []
    for n in nums:
        if n < primes[0]: # cannot be factorized.
            facs.append([n])
            continue
        if n in primes_set: # deal with prime directly.
            facs.append([1,n])
            continue
        fac_prime,fac_occ = [],[]
        ix, t = 0, n
        while t > 1: # find the prime factors.
            if t in primes_set: # t is a prime,
                fac_prime.append(t)
                fac_occ.append([0,1])
                break
            occ = 0
            while t > 1 and 0 == t % primes[ix]:
                occ += 1
                t //= primes[ix]
            if occ > 0:
                fac_prime.append(primes[ix])
                fac_occ.append(list(range(occ+1)))
                ix =  0
            else:
                ix += 1
        fac = [] # construct all its factors from its prime factor.
        for exps in product(*fac_occ):
            f = 1
            for j in range(len(fac_occ)):
                f *= fac_prime[j]**exps[j]
            fac.append(f)
        # now, fac contains all factors of i, including 1 and i itself.
        facs.append(fac)
    return facs


def test():
    # n = int(input().strip())
    mn,mx = 13, 89
    test_num = 10
    seed(time())
    nums = [randint(mn,mx) for _ in range(test_num)]
    # nums = [65]
    facs = factorize(nums)
    for n, fac in zip(nums,facs):
        print(n,sorted(fac))

if __name__ == '__main__':
    test()