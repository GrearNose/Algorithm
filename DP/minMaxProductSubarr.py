from random import seed, randint
from time import time

def min_max_product_subarr(arr):
    if None == arr or 0 == len(arr):
        return None
    mx_ix,mn_ix = 0,0
    mx_end,mn_end = arr[0],arr[0]
    mx_ln,mn_ln = 1,1
    max_ix,max_ln,max_p = mx_ix,mx_ln,mx_end
    min_ix,min_ln,min_p = mn_ix,mn_ln,mn_end

    for i in range(1,len(arr)):
        cur = mx_end*arr[i], mn_end*arr[i]
        if cur[0] > cur[1]:
            mx_end,mn_end = cur[0],cur[1]
            mx_ln,mn_ln = mx_ln+1,mn_ln+1
        else:
            mx_end,mn_end = cur[1],cur[0]
            mx_ln,mn_ln = mn_ln+1,mx_ln+1
            mx_ix,mn_ix = mn_ix, mx_ix
        if arr[i] > mx_end:
            mx_end,mx_ix,mx_ln = arr[i],i,1
        elif arr[i] < mn_end:
            mn_end,mn_ix,mn_ln = arr[i],i,1

        if mx_end > max_p:
            max_ix,max_ln,max_p = mx_ix,mx_ln,mx_end
        if mn_end < min_p:
            min_ix,min_ln,min_p = mn_ix,mn_ln,mn_end

        # print(i,arr[mx_ix:mx_ix+mx_ln],mx_end)
        # print(i,arr[mn_ix:mn_ix+mn_ln],mn_end)
    return (arr[min_ix:min_ix+min_ln],min_p),(arr[max_ix:max_ix+max_ln],max_p)

def test():
    ln = 10
    mn,mx = -3,8
    seed(time())
    arr = [randint(mn,mx) for _ in range(ln)]
    # arr = [5, 3, 0, 6, 3, 3, 0, 8, 3, 2]
    mnn,mxx = min_max_product_subarr(arr)
    print('arr:',arr)
    print('subarray with mn  product:',mnn)
    print('subarray with max product:',mxx)

if __name__ == '__main__':
    test()


