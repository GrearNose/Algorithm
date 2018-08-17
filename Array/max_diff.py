import random
from time import time

def max_diff(arr):
    """Find out the max difference of two elements in an unsorted array.
       N.B. this ensure that the difference is the result of the subtraction
       of the element sits before the other one in the array.
    """
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