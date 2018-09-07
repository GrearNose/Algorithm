from random import seed, randint
from time import time

def lower_bound_strict(arr,val):
    """
        Find the greatest element smaller than a given value in a
        non-descendingly sorted array using binary search, and return its index.
        Args
        arr: a ascendingly sorted array or vector
        len: number of elements in arr
        val: the element to search in arr
        return: index of the greatest elem < val if found, None otherwise.
    """
    if None == arr or 0 == len(arr) or val <= arr[0]:
        return None
    if val > arr[-1]:
        return len(arr)-1
    if 1 == len(arr):
        ix = 0 if arr[0] < val else None;
        return ix

    l, h = 0, len(arr)-1
    # now len >= 2, l < h, arr[0] < x <= arr[-1].
    while l < h:
        m = (l + h) >> 1
        if val > arr[m]: # ensure arr[l] < val always true.
            if l == m: # then l+1 == h, such that m = (l+h)/2 == l
                       # arr[m]=arr[l] < val <= arr[h], then arr[m] is the target.
                h = m
                break
            l = m
        else: # val <= arr[m]
            # there might be more than elem == val,
            # and in such case, we need to lower h to find
            # the greatest h, such that arr[h] < val.
            h = m - 1
            if arr[h] < val: # found the target
                break
    # now l == h, and note that arr[l] < val is always true,
    # and arr[h] is the greatest elem < val.
    return h


def lower_bound(arr, val):
    """"
        Find the greatest lower bound (i.e. the greatest elem <= val) of a given value
        in a non-descendingly, sorted array using binary search, and return its index.
        Args
        arr: a ascendingly sorted array or vector
        len: number of elements in arr
        val: the element to search in arr
        return: the index of the greatest elem <= val, if more than one are found,
                return the index of the FIRST one, None otherwise.
    """
    if None == arr or 0 == len(arr) or val < arr[0]:
        return None
    # not use '=' here in order to find the index of the first satifying elem.
    if arr[-1] <= val:
        return len(arr)-1
    if 1 == len(arr):
        ix = 0 if arr[0] <= val else None;
        return ix

    l, h = 0, len(arr)-1
    # now len >= 2, l < h, arr[0] < x <= arr[-1].
    while l < h:
        m = (l + h) >> 1
        if val > arr[m]:# ensure arr[l] < val always true.
            if l == m:  # then l+1 == h, (l+h)/2 == l, dead loop if not deal with it.
                        # that breaks the condition "val <= arr[h]".
                h = m
                break
            l = m
        else: # val <= arr[m]
            # there might be more than elem == val,
            # and in such case, we need to lower h to find
            # the greatest h value that breaks the upper bound
            # condition: arr[h] <= val.
            h = m - 1
            if arr[h] < val: # found the target
                break
    # now l == h, and note that arr[l] < val is always true,
    # and h = l is the greatest value that breaking the condition:
    # arr[h] >= val.
    # thus now, arr[h] < val <= arr[h+1], and arr[h+1] is the
    # (first if more than one) greatest lower bound.
    if arr[h+1] == val:
        return h + 1 # arr[h+1] is the first one of the greatest lower bound.
    else:             # N.B. in this case, arr[l] == arr[h] < x < arr[h+1]
        return h    # arr[h] is the greatest lower bound.


def upper_bound(arr,val):
    """
        Find the least upper bound of an given value 
        in a non-descendingly sorted array using binary search.
        Args
        arr: a ascendingly sorted array or vector
        len: number of elements in arr
        val: the element to search in arr
        return: the index of the the least elem >= val, if more that one are found,
             return the index of the LAST one, None if not found.
    """
    if None == arr or 0 == len(arr) or val > arr[-1]:
        return None
    # cannot use val <= arr[len-1] here, as there might be smaller upper bound.
    if val == arr[-1]:
        return len(arr)-1
    if val <= arr[0] or 1 == len(arr):
        ix = 0 if val <= arr[0] else None;
        return ix

    l, h = 0, len(arr)-1
    # now len >= 2, l < h, arr[0] < x <= arr[-1].
    while l < h:
        m = (l + h) >> 1

        if val < arr[m]: # ensure val < arr[h] always true.
            h = m
            if h > 1 and arr[h-1] < val:
                return h
        else: # arr[m] <= val
            # need to increase l to find the least l
            # that breaks the contidion of lower bound:
            # arr[l] <= val.
            l = m + 1
    # now l == h, arr[l-1] <= x < arr[l], arr[l-1] is
    # the last one satisfying the lower bound condition.
    if l > 1 and arr[l-1] == val: # arr[l-1] is the last one in the least upper bound.
        return l-1
    else:           # N.B. arr[l-1] < x < arr[l], 
        return l  # arr[l] is the least upper bound.



def upper_bound_strict(arr,val):
    """
        Find the strict upper bound of a value in a non-descendingly sorted array
        (i.e. the first elem > x) using binary search.
        Args
        arr: a ascendingly sorted array or vector
        len: number of elements in arr
        val: the element to search in arr
        return: the index of the index of the first elem > val if found, None otherwise.
    """
    if None == arr or 0 == len(arr) or val >= arr[-1]:
        return None
    if val < arr[0] or 1 == len(arr):
        ix = 0 if val < arr[0] else None;
        return ix

    l, h = 0, len(arr)-1
    # now len >= 2, l < h, arr[0] < x <= arr[-1].
    while l < h:
        m = (l + h) >> 1

        if val < arr[m]: # ensure val < arr[h] always true.
            h = m
        else: # arr[m] <= val
            # need to increase l to find the least l
            # that breaks the contidion of lower bound:
            # arr[l] <= val.
            l = m + 1
    # now l == h, arr[l-1] <= x < arr[l], arr[l] is
    # the first one breaking the lower bound condition.
    return l

def test_caller(arr, val, func, msg):
    if None  == arr or 0 == len(arr) or func == None:
         return False

    print(msg,end='')
    ix = func(arr,val)
    if None != ix:
        print( "arr[%d] = %d" %(ix,arr[ix]))
        return True
    else:
        print("Not found!")
        return False

def test():
    test_time = 3
    ln_mx = 3
    for ln in range(1,ln_mx+1):
        for _ in range(test_time):
            mn,mx = 3,23
            seed(time()) 
            arr = [randint(mn,mx) for _ in range(ln)]
            arr.sort()
            print('arr:',end = ' ')
            for a in arr: print(a,end=' ')
            print()
            # # use different cases for testing.
            # ix = randint(0,ln-1)
            # val = arr[ix]
            # val = arr[ix] - 1
            # val = arr[ix] + 1
            # val = arr[0]
            # val = arr[1]
            # val = arr[len(arr)-1]
            # val = arr[len(arr)-2]
            val =  randint(mn,mx)
            print('val to test:', val)

            flg1 = flg2 = flg3 = flg4 = False
            flg1 = test_caller(arr, val, lower_bound_strict, "strict lower bound: ")
            flg2 = test_caller(arr, val, lower_bound, "lower bound: ")
            flg3 = test_caller(arr, val, upper_bound, "upper bound: ")
            flg4 = test_caller(arr, val, upper_bound_strict, "strict upper bound: ")

            if flg1 and flg2 and flg3 and flg4:
                print('all found !')
            else:
                print('not all found!')

if __name__ == '__main__':
    test()
