def integer_mod(str_n, str_m):
    """
        Given number n and m, n can be very large and 0<n<10^9,
        calculate the result of n % m.
        str_n: the string of number n;
        str_m: the string of number m.
    """
    if None == str_n or None == str_m or 0 == len(str_n) or 0 == len(str_m):
        return None
    if not all([c.isdigit() for c in str_n]):
        return None
    m = int(str_m)
    md = 0
    for c in str_n:
        md = (md * 10 % m + ord(c) - ord('0')) % m
    return md

def test():
    n = '23862937412039480123423492308542134123947569347'
    m = '23846278'
    print(integer_mod(n,m))

if __name__ == '__main__':
    test()