def len_common_prefix(s,t):
    """
        get the length of the the common prefix of s and t.
    """
    if None == s or None == t or 0 == len(s) or 0 == len(t):
        return 0
    ln = min(len(s),len(t))
    for i in range(ln):
        if s[i] != t[i]:
            return i
    return 0

def longest_repeated_substr(s):
    """
        Find the longest repeated substring in the given string s,
        and return its index and length if found, None otherwise.
    """
    if None == s or 0 == len(s):
        return None
    ix_suffix_str = list(range(len(s)))
    ix_suffix_str.sort(key=lambda i: s[i:])
    for i in ix_suffix_str: print(i,s[i:])
    ix, ln_max = None, 0
    for i in range(len(ix_suffix_str)-1):
        p, q = ix_suffix_str[i],ix_suffix_str[i+1]
        ln = len_common_prefix(s[p:],s[q:])
        # print(p,q,ln)
        if ln > ln_max:
            ln_max = ln
            ix = p
    return ix,ln_max

def test():
    s = 'anbdanbs'
    s = 'abcddc'
    s = 'abcdef'
    s = 'dlapomd'
    print(s)
    ix,ln_max = longest_repeated_substr(s)
    # print(ix,ln_max)
    if None != ix:
        print('longest repeated substr:', ln_max, s[ix:ix+ln_max])
    else:
        print('Found None.')

if __name__ == '__main__':
    test()