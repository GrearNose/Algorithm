
def num_IS(n):
    """ Calculate the number of IS (Increasing Subsequence) of a certain length
        in all the permutation of n different number, and the length ranges
        from 1 to n.
        define the number of IS of length m in the permutation as NIS(n,m),
        then it has the following recurrenceformula:
        NIS(n,m) =
            sum(NIS(n-i,m-1) for i in [1,.,n-m+1]), if n>m>1;
            n, if n > m = 1;
            1, if n == m > 0.
        Not found a solu yet, maybe this is an ill-formed problem.
    """
    nis = [[1]*(i+1) for i in range(n+1)]
    for i in range(2,n+1):
        nis[i][1] = i # m == 1
        for j in range(2,i):
            nis[i][j] = sum([nis[i-k][j-1] for k in range(1,i-j+2)])
        nis[i][i] = 1  # n == m
    return nis

def test():
    nis = num_IS(8)
    for r in nis:
        for c in r:
            print('%3d'%c,end=' ')
        print()

if __name__ == '__main__':
    test()

