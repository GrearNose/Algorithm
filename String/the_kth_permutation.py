def the_kth_one_in_permutation(perm, k, show_procedure=False):
    """
       Re-order the elements in perm so that the result is the (k-1)th order
       in the whole permutation starting from the order in perm.
    """
    assert isinstance(perm, (list,tuple))
    assert isinstance(k,int)
    assert len(perm) > 0
    assert k > 0

    if show_procedure: print(perm, end = '')
    ln = len(perm)
    for i in range(k-1):
        # next_permutation algorithm:
        # two find, one swap, one reverse.
        # find the starting ix1 of the last ascending subsequence;
        # find the ix2 of min{perm[ix+1:]}
        # swap perm[ix1] and perm[ix2]
        # reverse perm[ix1+1:]
        found = False
        # find out the last ix where starts an ascending subseq.
        for j in reversed(range(ln-1)):
            if perm[j] < perm[j+1]: 
                found = True
                break
        if not found:
            print('Not found!', j)
            return None
        for k in reversed(range(j+1,ln)):
            if perm[k] > perm[j]: break
        # swap
        perm[j], perm[k] = perm[k], perm[j]
        if j+1 < ln-1: # reverse perm[j+1:]
            perm[j+1:] = perm[j+1:][::-1]
        if show_procedure: print('->', perm, end='')
    if show_procedure: print()

def test():
    x = list(range(3))
    # x = list('abc')
    cnt = 1
    for i in range(1,len(x)+1): cnt *= i
    for i in range(1,cnt+1):
        cp = x.copy()
        the_kth_one_in_permutation(cp,i, True)
        # print(cp)

if __name__ == '__main__':
    test()