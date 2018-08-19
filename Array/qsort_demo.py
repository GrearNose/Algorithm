from random import  randint,seed
from time import time


def qsort1(arr,start=None,end=None):
    """Exercise for the qsort algorithm.
        === Args ===
        arr: the array to sort;
        start: the starting index of the segment to sort;
        end: the ending index of the segment to sort.
    """
    if None == start:
        start = 0
    if None == end:
        end = len(arr) - 1
    if None == arr or start >= end:
        return
    assert 0 <= start
    assert end < len(arr)

    pivot = arr[start]
    i,j = start,end
    while i < j:
        while i < j and arr[i] <= pivot:
            i += 1
        while i < j and arr[j] >= pivot:
            j -= 1
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]

    # there are many cases about the final value of i:
    # 1. len(arr) = 2, then i = j = 1, 
    #    the relationship between pivot and arr[i] is not clear.
    # 2. arr[1:] > pivot, i = j = 1, arr[i] = arr[1] > pivot
    # 3. arr[1:] < pivot, i = j = len(arr)-1, arr[i] = arr[-1] < pivot
    # 4. general case, i = j, arr[:i] <= pivot, pivot <= arr[i+1:], 
    #   the relationship between pivot and arr[i] is not clear.
    if pivot > arr[i]:
        arr[start],arr[i] = arr[i],arr[start]
        ix_pv = i
    elif i > 1 and arr[i-1] <= pivot:
        arr[start],arr[i-1] = arr[i-1],arr[start]
        ix_pv = i-1
    else:
        ix_pv = start # pivot keeps unmoved.

    # and not use slice of arr, as that will pass a copy as param.
    qsort1(arr,start,ix_pv-1)
    qsort1(arr,ix_pv+1,end)


def qsort2(arr,start=None,end=None):
    """Another implementation."""
    if None == start:
        start = 0
    if None == end:
        end = len(arr) - 1
    if None == arr or start >= end:
        return
    assert 0 <= start
    assert end < len(arr)

    pivot = arr[start]
    i,j = start,start+1
    # arr[:i+1] <= pivot
    # arr[i:j] > pivot
    for j in range(start+1,end+1):
        if arr[j] <= pivot:
            i += 1
            if i < j:
                arr[i],arr[j] = arr[j],arr[i]

    if arr[start] > arr[i]:
        arr[start],arr[i] = arr[i],arr[start]

    qsort2(arr,start,i-1)
    qsort2(arr,i+1,end)


def qsort3(arr,start=None,end=None):
    """A implementation from the textbook."""
    if None == start:
        start = 0
    if None == end:
        end = len(arr) - 1
    if None == arr or start >= end:
        return    
    if None == arr or len(arr) < 2:
        return
    pivot = arr[start] # fetched arr[0] as pivot, and treat arr[0] as empty space.
    i,j = start,end
    while i < j:
        while i < j and arr[j] >= pivot:
            j -= 1
        # as arr[i] is 'empty', move arr[j] to arr[j]
        arr[i] = arr[j] # now arr[j] is 'empty'.
        while i < j and arr[i] <= pivot:
            i += 1
        arr[j] = arr[i] # arr[i] is 'empty' again.
    arr[i] = pivot # move the pivot to the 'empty' place, the correct position.

    qsort3(arr,start,i-1)
    qsort3(arr,i+1,end)


def test():
    seed(time())
    mn,mx = 0,13
    ln = 23
    arr1 = [ randint(mn,mx) for _ in range(ln)]
    arr2 = arr1.copy()
    arr3 = arr1.copy()
    arr0 = sorted(arr1)
    print('original array:  ', arr1)
    print('correctly sorted:', arr0)
    qsort1(arr1,0,len(arr1)-1)
    qsort2(arr2)
    qsort3(arr3)

    if arr1 == arr0:
        print('qsort1: correct!')
    else:
        print('qsort1: wrong!', arr1)

    if arr2 == arr0:
        print('qsort2: correct!')
    else:
        print('qsort2: wrong!', arr2)

    if arr3 == arr0:
        print('qsort3: correct!')
    else:
        print('qsort3: wrong!', arr3)

if __name__ == '__main__':
    test()