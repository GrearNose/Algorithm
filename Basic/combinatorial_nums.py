def combinatorial_number(n):
    """ calculate the Pascal's triangle, i.e. the combinatorial triangle,
        starting from 0 to n, the i-th row and and the j-th col (j<=i) is
        the combinatorial number C(i,j).
        === Args ===
        n: a positive integer specifying the heigth of the triangle.
        return: a list, of which the i-th element is a list of combinatorial
        numbers corresponding the i-th row of the Pascal triangle.
    """
    assert isinstance(n,int)
    assert n > 0
    C = [[1]*(i+1) for i in range(n+1)]
    for i in range(2,n+1):
        for j in range(1,i//2+1):
            C[i][j] = C[i-1][j] + C[i-1][j-1]
            C[i][i-j] = C[i][j]
    return C

def test():
    test_num = 10
    mn = 2
    for i in range(mn,mn+test_num):
        C = combinatorial_number(i)
        print(i)
        for c in C:
            print(c)

if __name__ == '__main__':
    test()