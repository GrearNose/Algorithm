from random import randint
from time import time
from collections import Counter

def converge_as_three_segs(arr,three_val):
    """Given an array with element of 3 different values,
       converge its elements into 3 consecutive subsequences.
    """
    assert None != arr
    assert None != three_val
    assert len(arr) > 0
    assert 3 == len(three_val)

    # indices at head, current, end
    # build the three segments by moving h and c forward,
    # e backward, and maintain the following property:
    # arr[:h]  == three_val[0]
    # arr[h:c] == three_val[1]
    # arr[e+1:]  == three_val[2]
    h, c, e = 0, 0, len(arr)-1
    while c <= e:
        # print(h,c,e, arr)
        # break the property, swap arr[h] and arr[c]
        # to maintain it.
        if arr[c] == three_val[0]:
            if h < c:
                arr[h],arr[c] = arr[c],arr[h]
            h += 1 # arr[h] is the first one equals to three_val[1]
            c += 1
        # not break the property, no swapping.
        elif arr[c] == three_val[1]:
            c += 1
        # break the property, move arr[c] to the end by swapping arr[c]
        # and arr[e], and keep c unchanged in case that arr[c] != three_val[1],
        # which breaks the property, and in this case, arr[c] will be swapped
        # in the next iter.
        elif arr[c] == three_val[2]:
            arr[c],arr[e] = arr[e],arr[c]
            e -= 1 # now that arr[e] == three_val, move e backward.
        else:
            raise Exception("arr[%d] has value '%s' not in the given three_val: '%s'"%(c, str(arr[c]), str(three_val)))

def test():
    ln = 23
    arr = [0] * ln
    three_val = 'RGB'
    # three_val = [0,1,2]
    # arr = [randint(0,2) for _ in range(ln)]
    for i in range(ln):
        ix = randint(0,len(three_val)-1)
        arr[i] = three_val[ix]

    cnt0 = Counter(arr)
    print('original arr:')
    print(arr)
    converge_as_three_segs(arr,three_val)
    print('converged:')
    print(arr)
    cnt1 = Counter(arr)
    is_sorted = True
    for i in range(1,ln):
        if arr[i-1] > arr[i]:
            is_sorted = False
            break
    if is_sorted:
        if cnt0 == cnt1:
            print("correct!")
        else:
            print("inconsistent in counting: ", cnt0, " vs. ", cnt1)
    else:
        print("unsorted!")

if __name__ == '__main__':
    test()


