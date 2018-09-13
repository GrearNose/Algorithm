from math import ceil

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


def primes_get_more(primes, n_extra):
    """ 
    Get n_extra more prime numbers given the previous prime number.
    ==== Args ====
    primes: the previous prime numbers starting with 2;
    n_extra: the amount of extra prime numbers to get.
    return: None. The extra prime numbers will be appended to 'primes'.
    """
    assert isinstance(primes, list)
    assert n_extra > 0
    if 0 == len(primes):
        primes = [2]
    for cnt in range(n_extra):
        num = 1 + primes[-1] # the first number to try
        found = False
        while not found:
            upper = ceil(num**.5)
            is_prime = True
            for p in primes:
                if 0 == num % p:
                    is_prime = False
                    break
                if p >= upper: # found a prime number.
                    break
            if is_prime:
                primes.append(num)
                found = True
            num += 1

def test():
    n = 35
    primes = primes_sifting(n)
    print(primes)
    n_extra = 3
    primes_get_more(primes,n_extra)
    print('get %d more primes:'%n_extra)
    print(primes)

if __name__ == '__main__':
    test()