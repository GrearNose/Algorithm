def longest_substr_of_repeated_char(s):
    if None == s or 0 == len(s):
        return None
    ix,ix_mx,ln_mx = 0,0,0
    for i in range(1,len(s)):
        if s[i] != s[ix] or i == len(s) - 1:
            if i-ix>ln_mx:
                ln_mx = i-ix
                ix_mx = ix
            ix = i-1
    return ix_mx,ln_mx

def test():
    s = 'asdfallllaaabdddddssssdlseeee'
    ix,ln = longest_substr_of_repeated_char(s)
    print(s)
    print(ix,ln,s[ix:ix+ln])

if __name__ == '__main__':
    test()