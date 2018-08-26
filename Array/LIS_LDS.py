def LIS(a,B0=None,ix_b=None):
    """
        Longest Increasing Subsequence(LIS).
        === Args ===
        a: the sequence to search;
        B0: the record of the result of last search;
        ix_b: the begining index of the given array in current search.
        return: len of LIS.
    """
    if None == a or 0 == len(a):
        return 0
    if None != B0:
        if 0 == len(B0):
            B0.append(a[0])
            ix_b = len(B0)
        B = B0
    else:
        B = [a[0]]
        ix_b = 1

    for v in a[ix_b:]:
        l,h = 0,len(B)-1
        while l <= h:
            m = (l+h) >> 1 # (l+h) // 2
            if v < B[m]: # search left part
                h = m-1
            elif v > B[m]: # search right part
                l = m+1
            else:
                break
        if l > h: # not found
            # now, l > h, l = h + 1
            # B[l] is the least uppper bound.
            # B[h] is the greatest lower bound.
            # update the least one > v with v,
            # i.e. B[l]
            if l >= len(B):
                B.append(v)
            else:
                B[l] = v
    return len(B)

def LIS_LDS(a,seq=None):
    """
        the longest subsequence whose first is increasing and
        the second part is decreasing.
        === Args ===
        a: the array in which the LIS_LDS is to be search.
        seq: the list to hold the LIS_LDS sequence.
        return: len of LIS_LDS.
    """
    h = [a[0]]
    for i in a[1:]: # remove consective duplicated ones.
        if i != h[-1]:
            h.append(i)

    ln = len(h)
    B_l,B_r   = [],[]
    lens_l,lens_r = [0],[0]
    for i in range(1,ln+1):
        seq_l,seq_r = h[:i],h[-i:][::-1]
        len_l      = LIS(seq_l, B_l, i-1)
        len_r      = LIS(seq_r, B_r, i-1)
        lens_l.append(len_l)
        lens_r.append(len_r)

    ln_mx = 0
    for i in range(ln+1):
        j    = ln - i
        ln_c = lens_l[i] + lens_r[j]
        if ln_c > ln_mx:
            ln_mx = ln_c
    return ln_mx

def test():
    # input() # ignore the 'n' indicating the number of input.
    # h0 = [int(x) for x in input().split()]
    a = [186,186,150,200,160,130,197,200]
    ln = LIS_LDS(a)
    print(ln)

if __name__ == '__main__':
    test()