def longest_palindrome(s):
    """
        Find the length of the longest palindrome.
        === Args ===
        s: the string to search.
        return the longest palindrome.
    """
    if None == s or 0 == len(s):
        return None
    ln = len(s)
    ln_mx = 0
    ix_b,ix_e = 0,0
    for i in range(len(s)):
        # for odd-length palindrome
        j = 1
        while (i-j) >= 0 and (i+j) <= ln-1 and s[i-j] == s[i+j]:
            j += 1
        if ln_mx < 1+2*(j-1):
            ln_mx = 1+2*(j-1)
            ix_b,ix_e = i-j+1, i+j-1

        # for even-length palindrome
        j = 1
        while (i-j+1) >= 0 and (i+j) <= ln-1 and s[i-j+1] == s[i+j]:
            j += 1
        if ln_mx < 2*(j-1):
            ln_mx = 2*(j-1)
            ix_b,ix_e = i-j+2, i+j-1

    return s[ix_b:ix_e+1]

def test():
    while True:
        s = input()
        p = longest_palindrome(s)
        print(len(p),p)

if __name__ == '__main__':
    test()