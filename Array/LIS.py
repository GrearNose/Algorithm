
def lis(arr):
    """ find out the longest increasing subsequence."""
    if arr == None or not isinstance(arr, (list,tuple)) or len(arr) == 0:
        return None
    B = [arr[0]]
    # subLIS a map to record the sequence with the smallest ending found currently.
    # key: the subsequence len, value: the sequence of len key.
    # N.B. when only the lenght is need not the sequence, then don't use it.
    subLIS = {1:[arr[0]]}
    ln = 1
    for i in range(1,len(arr)):
        # ix = lower(B,arr[i])
        # if ix != None and ix != False:
        x = arr[i]
        # print("B,subLIS,x:", B, subLIS,x)
        if x > B[-1]:
            tmp = subLIS[len(B)].copy()
            B.append(x)
            tmp.append(x)
            subLIS[len(B)] = tmp # copy the current longest subsequnce.
        elif x < B[0]:
            B[0] = x
            subLIS[1] = [x]
        elif B[0] < x and x < B[-1]: # there must be an ix such that B[ix] <= x < B[ix+1]
            # print("B,i,x:",B, i, x)
            ix = None
            l,h = 0,len(B)-1
            while l < h:
                mid = (l+h)>>1
                if x < B[mid]:
                    h = mid - 1
                elif x > B[mid]:
                    l = mid + 1
                else: 
                    ix = mid
                    break
            if not ix:
                ix = l
            # print("B:",B)
            # print("replace B[%d] with %d"%(ix,x))
            B[ix] = x
            tmp = subLIS[ix+1]
            tmp[-1] = x
            subLIS[ix+1] = tmp
    return B,subLIS[list(subLIS.keys())[-1]]

def test():
    arr = [[2, 1, 5, 3, 6, 4, 8 ,9, 7],\
            [2,3,5,2,1,7,3,8,5,9]]
    for a in arr:
        print('arr:',a)
        B,LIS = lis(a)
        print("B,LIS:",B,LIS)

if __name__ == '__main__':
    test()

