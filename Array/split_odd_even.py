from random import randint
from time import time

def split_odd_even(arr):
    """Split an array into two parts such that the first part (in front of the array)
        contain all odd nums, and the second part(in rear of the array) contains all
        even nums.
       arr: a list of integers to split, and it will be modified.
       return None.
       algorithm: use two indices, i and j, to traverse the array from its
         two ends towards its center, and swap arr[i], arr[j] when arr[i]
         is even and arr[j] is odd.
    """

    if None == arr or len(arr) < 2:
        return None
    assert isinstance(arr,list)
    i,j = 0,len(arr)-1
    while i < j:
        while i < j and 1 == arr[i] % 2:
            i += 1
        while i < j and 0 == arr[j] % 2:
            j -= 1
        arr[i],arr[j] = arr[j], arr[i]

def test():
    mn,mx = -13,13
    ln = 23
    arr = [randint(mn,mx) for _ in range(ln)]
    print(arr)
    split_odd_even(arr)
    print(arr)

if __name__ == '__main__':
    test()