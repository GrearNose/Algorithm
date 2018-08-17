import random
from time import time

def max_diff(arr):
    """Find out the max difference of two elements in an unsorted array.
       N.B. the difference is the result of the subtraction
       of two element arr[i] and arr[j], where 0 <= i < j < len(arr).
    """
    assert None != arr
    assert len(arr) > 1
    mx,mx_dif = arr[0],0
    for i in range(1,len(arr)):
        dif = mx - arr[i]
        mx_dif = max(mx_dif,dif)
        mx = max(mx,arr[i])
    return mx_dif

def test():
    random.seed(time())
    num = 13
    m,mx = 1,14
    x = [random.randint(m,mx) for _ in range(num)]
    print(x)
    print(max_diff(x))

if __name__ == '__main__':
    test()