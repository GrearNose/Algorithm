from random import randint,seed
from time import time

def get_next(p):
    assert isinstance(p, str),'s,p should be str'
    if len(p) == 0:
        return None

    # Try to find a k, such that
    #       p[:k] == p[j-k:j], 0 < k < j, (N.B. k<j, k!=j, so k <= j-1)
    # if such k exist, use the max one, and set next_pos[j] to k;
    # otherwise, set next_pos[j] to 0.
    # Note that, when j == 0, i.e. when s[i] != p[0], then, the next two
    # char to compare is s[i+1] and p[0], so set a special value -1
    # to indicate that i should be increased, and keep j unchanged.
    # In summary, 
    #  next_pos[j] =
    #       -1, j == 0
    #       max{k| p[:k] == p[j-k:j], 0 < k < j}, if j > 0 and k exists;
    #       0, j > 0 and k does not exists.
    # ==== Algorithm ====
    # To find the max k, it's equivelant to do a string match with p[1:j]
    # as the main str, and p[:j] as the pattern str, and use i and j as their
    # indices respectively:
    # N.B. when strlen <=2, 
    # there are not two identical substrs in the head and tail.
    next_pos    = [0] * len(p)
    i = 1         # index for the main str p[1:j], intialized with 1;
    j = 0         # index of the pattern str p[:j], initialized with 0.
    while i < len(p)-1:
        if p[i] == p[j]: # go on to compare the next one of both strs.
            i += 1
            j += 1
            # found two identical substr: p[i-j:i] == p[:j],
            # (but cannot ensure p[i] == p[j]),
            # so when s[k] != p[i], the next two chars to compare
            # are s[k] and p[j], thus set next_pos[i] to j.
            next_pos[i] = j
        elif 0 == j:      # p[i] != p[0], need to compare p[i+1] with p[0]
            i += 1
            # next_pos[i] = 0 # no need to set it as it has the default value 0.
        else:             # p[i] != p[j], need to compare p[i] with p[next_pos[j]]
            assert j < len(p), str(i,j,next_pos)
            j = next_pos[j]
    return next_pos


def str_find(s,p):
    assert isinstance(s, str) and isinstance(p, str),'s,p should be str'
    if len(s) == 0 or len(p) == 0 or len(s) < len(p):
        return None # not found
    # print('getting nexpos ...')
    next_pos = get_next(p)
    # print('next_pos:',next_pos)
    i,j = 0,0
    while i < len(s) and j < len(p):
        if s[i] == p[j]:
            i += 1
            j += 1
        elif j == 0:
            i += 1
        else:
            j = next_pos[j]
    if j == len(p):
        return i - len(p)
    else:
        return None

def test0():
    s = 'abcdasasdoifjggf'
    p = 'sasdo'
    print(s, p, 'starting index:', str_find(s,p))


def test():
    seed(time())
    strlen = 1000
    s = [randint(ord('a'),ord('z')) for _ in range(strlen)]
    s = [chr(asc) for asc in s]
    s = ''.join(s)
    ix_substr = []
    test_cases = []
    test_num = 10000
    for i in range(test_num):
        ix_s = randint(0,len(s)-3)
        ln =   randint(3,len(s)-ix_s)
        ix_e = ix_s + ln
        ix_substr.append((ix_s,ix_e))
        t = [0]*ln
        for j in range(ln):
            t[j] = s[ix_s+j]
        t = ''.join(t)
        test_cases.append(t)
    print('the main str of len %d:\n'%strlen, s)
    t0 = time()
    print('testing with kmp ...')
    for i in range(test_num):
        ix_s,ix_e = ix_substr[i]
        # t = s[ix_s:ix_e]
        t = test_cases[i]
        ix = str_find(s,t)
        assert ix == ix_s or s[ix:ix+(ix_e-ix_s)] == t, \
           'found %d vs. ground truth %d, %s vs. %s'%(ix_s,ix,\
           s[ix:ix+(ix_e-ix_s)], t)
        # print(ix==ix_s,ix,ix_s,t)
        # print(ix==ix_s,ix,ix_s)
    t1 = time()
    print('testing with in ...')
    for i in range(test_num):
        # ix_s,ix_e = ix_substr[i]
        # t = s[ix_s:ix_e]
        t = test_cases[i]
        # t in s
        assert t in s
    t2 = time()

    print("Passed all the test cases.\ntime consumption, kmp vs. 'in': ", t1-t0, t2-t1)
    # ==== Testing result ====
    # Passed all test case in serval runs. But the self-defined func takes much
    # more time than str's built-in func 'in', about 300 times more.
    # Thus, str's built-in func 'in' has already been well optimized.

if __name__ == '__main__':
    test()