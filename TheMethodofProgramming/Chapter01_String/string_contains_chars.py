def str_contains_chars(s,t):
    """
    Given two string s and t, determind
    if s contains all chars in t.
    """
    set1 = set(s)
    set2 = set(t)
    # print(set1,set2, set2.issubset(set1))
    return set2.issubset(set1)

def str_contains_chars_bitmap(s,t):
    """Use a bitmap to count the occurance of chars."""
    bitmap = [False] * 256 # assume all chars are ascii.
    for c in s:
        ix = ord(c)
        bitmap[ix] = True
    for c in t:
        ix = ord(c)
        if not bitmap[ix]:
            return False
    return True

def str_contains_chars_bitmap_signature(s,t):
    """Use bits in an int variable to record the occurance of chars."""
    m = 0
    for c in s:
        m |= 1<<ord(c)
    for c in t:
        if not(m & (1<<ord(c))):
            return False
    return True

def test():
    s  = 'algasgapset'
    t1 = 'abc'
    t2 = 'ags'
    print('%s,%s:'%(s,t1),str_contains_chars(s,t1),\
        str_contains_chars_bitmap(s,t1), str_contains_chars_bitmap_signature(s,t1))
    print('%s,%s:'%(s,t2),str_contains_chars(s,t2),\
        str_contains_chars_bitmap(s,t2), str_contains_chars_bitmap_signature(s,t2))

if __name__ == '__main__':
    test()