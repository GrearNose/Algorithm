import random
from time import time

def shortest_seq(seq,threshold,dbg=False):
    """Find the shortest subsequence with a sum not less than threshold.
       ===Args===
       seq: the sequence to search;
       threshold: sum threshold;
       dbg: a flag to print the debug info.
       return: a tuple (ix,len) where ix is the starting index of the found
       sequnce and len the length of the subsequnce, if found; None otherwise.
    """
    assert None != seq
    assert None != threshold
    assert len(seq) > 0
    s_cur,s_min = 0,0 # current sum and minimum sum found.
    ix,ix_min   = 0,0
    ln,ln_min   = len(seq),len(seq)
    cnt_neg     = 0   # count of the negative number within the sequence.
    found       = False # whether a solu has been found.
    for i in range(len(seq)):
        if s_cur > 0:
            s_cur += seq[i]
            if seq[i] < 0:
                cnt_neg += 1
        else:
            s_cur = seq[i]
            ix = i
            cnt_neg = 1 if seq[i] < 0 else 0

        if dbg: print(seq[ix:i+1],s_cur)

        if s_cur >= threshold: # found one solu.
            found = True
            # try to find a shorter one ending with seq[i] only when seq[i] > 0,
            # and there no shorter one if seq[i] <= 0.
            if seq[i] > 0:
                # no negative num within seq[ix:i+1], trim from left-size.
                if 0 == cnt_neg:
                    if dbg: print('trim left size')
                    while s_cur - seq[ix] >= threshold:
                        s_cur -= seq[ix]
                        ix += 1
                # negative exists, try find a shorter sequence ending
                # with seq[i] by constructing it backward starting from seq[i].
                else:  # cnt_neg > 0
                    if dbg: print('construct from right size')
                    cnt_neg = 0
                    s_tmp = 0
                    for j in range(i,ix-1,-1):
                        s_tmp += seq[j]
                        if seq[j] < 0:
                            cnt_neg += 1
                        if s_tmp >= threshold: break
                        # no need to continue the search when its length >= ln_min
                        if i - j + 1 >= ln_min: break
                    if ix < j and s_tmp >= threshold:
                        ix = j
                        s_cur = s_tmp
                        if dbg: print('found shorter:',seq[ix:i+1],"sum:%d, ln:%d"%(s_cur,i-j+1))
            ln = i - ix + 1
            if ln < ln_min:
                if dbg: print('replace')
                ln_min = ln
                ix_min = ix
                s_min  = s_cur
                if 1 == ln_min: # cannot be shorter.
                    break
    if found:
        return (ix_min,ln_min,s_min)
    else:
        return None

def test():
    random.seed(time())
    num = 13
    m,mx = -3,3+3+1
    arr = [random.randint(m,mx) for _ in range(num)]
    th = random.randint(-m,3*mx)
    print('array:',arr)
    print('sum threshold:', th)
    # rslt = shortest_seq(arr,th,True)
    rslt = shortest_seq(arr,th)
    if None != rslt:
        ix,ln,s = rslt
        print("ix:%d, len:%d, sum:%d"%(ix,ln, s), arr[ix:ix+ln])
    else:
        print('No subsequence !')

if __name__ == '__main__':
    test()
