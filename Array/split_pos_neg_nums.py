from random import randint
from time import time

def split_pos_neg(arr):
    """Split an array into two parts such that the first part (in front of the array)
        contain all positive nums, and the second part(in rear of the array) contains all
        negative nums.
       arr: a list of integers to split, and it will be modified.
       return None.
       algorithm: use two indices, i and j, to traverse the array from its
         two ends towards its center, and swap arr[i], arr[j] when arr[i]
         is negative and arr[j] is positive.
    """

    if None == arr or len(arr) < 2:
        return None
    assert isinstance(arr,list)
    i = -1
    for j in range(len(arr)):
        # use this to split negative nums to the front, positive nums to the rear.
        # if arr[j] < 0:
        if arr[j] > 0:
            i += 1
            if i < j:
                arr[i],arr[j] = arr[j], arr[i]
                # print(arr[:j+1])


def test():
    mn,mx = -13,13
    ln = 23
    arr = [randint(mn,mx) for _ in range(ln)]
    print(arr)
    split_pos_neg(arr)
    print(arr)

if __name__ == '__main__':
    test()