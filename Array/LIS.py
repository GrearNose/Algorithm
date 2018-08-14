
def lis(arr):
    """ Find out the LIS(longest increasing subsequence) of an array,
        using a DP algorithm with complexity of o(nlogn).
    """
    if arr == None or not isinstance(arr, (list,tuple)) or len(arr) == 0:
        return None

    # B is an auxiliary array used in this DP algorithm, and B[ix] records
    # the smallest ending element of the sequence of length ix+1, found
    # during the traversal through the given array arr.
    B = [arr[0]] # initialized with the first elem of arr.

    # subLIS a map to record the sequence with the smallest ending found
    # currently.
    # key: the len of LIS, value: the LIS.
    # N.B. not need to use it when only the length of LIS is required,
    # but not the sequence.
    subLIS = {1:[arr[0]]} # initialized with the first elem of arr.
    for i in range(1,len(arr)): # go through arr, and update B and subLIS.
        x = arr[i] # fetch the current elem.

        # x is larger than the last elem of the current longest LIS of arr[0,.,i],
        # then append x to the tail of this LIS, and make a copy to subLIS.
        if x > B[-1]:
            # use copy, not reference, and must copy it before the appending,
            # otherwise subLIS[len(B)] wound not exist.
            cpy = subLIS[len(B)].copy()
            B.append(x)
            cpy.append(x)
            subLIS[len(B)] = cpy # copy the current longest LIS of arr[0,.,i].

        # x is  smaller than the first elem in B, i.e. found a subsequence
        # of lenght with a smaller ending element, then update both B[0]
        # and subLIS[1].
        elif x < B[0]:
            B[0] = x
            subLIS[1] = [x]

        # there must be an ix such that B[ix] <= x < B[ix+1],
        # find it by using bisearch. 
        elif B[0] < x and x < B[-1]:
            # use bisearch to find out the smallest elem in B, B[ix] which is
            # larger than x. if such elem is found, update the subsequence of
            # length ix+1 by replacing its last elem with x.
            ix = None
            l,h = 0,len(B)-1
            # compare until l > h.
            # N.B. when l==h, x > B[l], then the pos ix should be l+1.
            while l <= h:
                mid = (l+h) >> 1 # i.e. mid = (l+h) // 2
                if x < B[mid]:
                    h = mid - 1
                elif x > B[mid]:
                    l = mid + 1
                else: 
                    ix = mid
                    break
            # No B[ix]==x is found, then l >= h, thus B[l] > x,
            # B[l] is the smallest elem in B larger than x.
            if None == ix:
                ix = l
            # update them only when a smallest B[ix] > x is found,
            # otherwise, B[ix] == x, not need to update.
            if x < B[ix]:
                # B[ix] is the ending elem of the sequence of length ix+1.
                B[ix] = x
                # update the corresponding subsequence in the subLIS.
                # N.B. subLIS[ix+1] is the LIS of length ix+1.
                subLIS[ix+1][-1] = x

    # extract the longest LIS.
    mxLen = list(subLIS.keys())[-1]
    subLIS = subLIS[mxLen]

    return B,subLIS

def test():
    arr = [[2, 1, 5, 3, 6, 4, 8 ,9, 7],\
            [2, 3, 5, 2, 1, 7, 3, 8, 5, 9],
            [10, 17, 4, 19, 14, 2, 10, 6, 17, 10]]
    for a in arr:
        B,LIS = lis(a)
        print('arr:',a)
        print("B:",B)
        print("LIS:",LIS)
        print()

if __name__ == '__main__':
    test()

