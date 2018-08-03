def prime_factorize(n):
    occurance, i = {}, 2
    while(i*i <= n):
        cnt = 0
        while(n%i==0):
            n /= i
            cnt += 1
        if cnt > 0:
            occurance[i] = cnt
        i += 1
    if n > 1:
        occurance[n] = 1
    return occurance

def test(upper):
    passed = True
    for n in range(1,upper+1):
        factors = prime_factorize(n)
        prod = 1
        print(n, 'factors:', factors)
        for factor,occ in factors.items():
            for i in range(occ):
                prod *= factor
        if prod != n:
            print('Wrong!  %d vs %d'%(n,prod))
            passed = False
    if passed:
        print('Passed all test within  range [%d,%d]'%(1,upper))
    else:
        print('Does not pass all test')

if __name__ == '__main__':
    test(5273)