from random import randint, seed
from time import time

def search_matrix(arr,val):
    """
        Given a sorted matrix, i.e. arr[i][j] > max(arr[i-1][j],arr[i][j-1]),
        and a value val, search it in this matrix.
        === Args ===
        arr   the matrix, a list of list of numbers;
        val   the value to search, a number.
        return a tuple (r,c) if arr[r][c]==val is found, None otherwise.
    """
    if None == arr or None == val or 0 == len(arr):
        return None
    assert all([len(arr[0]) == len(row) for row in arr]) # all rows have same length.

    r,c = 0,len(arr[0])-1
    while r < len(arr) and c >= 0:
        if val < arr[r][c]:
            c -= 1   # exclude arr[:][c], search arr[r:][:c-1]
        elif val > arr[r][c]:
            r += 1   # exclude arr[r][:], search arr[r+1:][:c]
        else:        # found
            return (r,c)
    return None

def test():
    row_mx,col_mx = 8,9
    inc_mx = 3
    seed(time())
    row = randint(1,row_mx)
    col = randint(1,col_mx)
    arr = [[0]*col for _ in range(row)]
    for j in range(col):
        arr[0][j] = arr[0][j-1] + randint(1,inc_mx)
    for i in range(1,row):
        arr[i][0] = arr[i-1][0] + randint(1,inc_mx)
        for j in range(1,col):
            prev = max(arr[i][j-1],arr[i-1][j])
            inc = randint(1,inc_mx)
            arr[i][j] = prev + inc
    print("matrix:")
    for r in arr:
        print("[",end="")
        for v in r:
            print("%2d"%v,end=" ")
        print("]")

    val = randint(arr[0][0],arr[-1][-1])
    print("val to search:", val)

    indices = search_matrix(arr,val)

    if None == indices:
        print("not found !")
    else:
        print("indices:", indices)

if __name__ == '__main__':
    test()