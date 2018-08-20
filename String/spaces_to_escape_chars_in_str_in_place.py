def space_to_escape_chars(s):
    """
        convert the space characters into special chars '%20' in a string
        in place without using extra memory space except for the necessary
        for storing.
    """
    assert isinstance(s,str)
    num_space = s.count(' ')
    if 0 == num_space:
        return s
    else:
        arr = list(s)
        arr += ['0']*(3-1)*num_space
        i = len(s)-1
        j = len(arr)-1
        while i < j:
            if ' ' != arr[i]:
                arr[j] = arr[i]
                j -= 1
            else:
                arr[j:j-3:-1] = "%20"
                j -= 3
            i -= 1
    return ''.join(arr)

def test():
    s = "Je t'aime mon amour! Ne quittez pas!"
    s3 = space_to_escape_chars(s)
    print('original str:', s)
    print('converted str:', s3)

if __name__ == '__main__':
    test()