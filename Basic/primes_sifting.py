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

def test():
    n = 101
    print(primes_sifting(n))

if __name__ == '__main__':
    test()