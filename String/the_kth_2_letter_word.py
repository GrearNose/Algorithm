from the_kth_permutation import the_kth_one_in_permutation

def combinatorial_number(n):
    """ calculate the Pascal's triangle, i.e. the combinatorial triangle,
        starting from 0 to n, the i-th row and and the j-th col (j<=i) is
        the combinatorial number C(i,j).
        === Args ===
        n: a positive integer specifying the heigth of the triangle.
        return: a list, of which the i-th element is a list of combinatorial
        numbers corresponding the i-th row of the Pascal triangle.
    """
    assert isinstance(n,int)
    assert n > 0
    C = [[1]*(i+1) for i in range(n+1)]
    for i in range(2,n+1):
        for j in range(1,i//2+1):
            C[i][j] = C[i-1][j] + C[i-1][j-1]
            C[i][i-j] = C[i][j]
    return C

def the_kth_2_letter_word(two_letters, n1, n2, k, C=None,dbg=False):
    """A 2-letter word is a word consisting of two unique letters, 
       such as '001', 'aba', 'abbb', etc. The k-th of such word is
       k-th one (in alphabet order) in the dict.
       ===Args===
       two_letters: a list or tuple of two different comparable elements;
       n1: num of two_letters[0] composing this word;
       n2: num of two_letters[1] composing this word;
       k:  an int to indicate the k-th word to find;
       C:  a n-by-n matrix recording the combinatorial number with 
           index as the input to C(n,m).
       dbg: a flag to print the debug info if set True.
       return: the k-th word in alphabet consisting of n1 two_letters[0]
                and n2 two_letters[1].
    """
    assert isinstance(two_letters, (list,tuple))
    assert len(two_letters) == 2
    assert isinstance(k,int)
    assert k > 0

    n  = n1 + n2
    m  = n1
    k0 = k

    if None == C or len(C) < n:
        C = combinatorial_number(n)

    if k > C[n][m]:
        return None # out of the range of the dict.

    # dict size: C(n,m)
    # basic equation in this algorithm: C(n,m) = C(n-1,m-1) + C(n-1,m)
    word = [3] * n
    ix   = 0
    while k > 0:
        if dbg: print(ix,k,word)
        # 0 < k < C(n-1,m-1)
        # then the ix-th letter is two_letters[0],
        # and the k-th word is smaller than the C(n-1,m-1)-th word.
        # It's equal to find the k-th word of length n-1, consisting
        # of m-1 two_letters[0] and n-(m-1) two_letters[1].
        if m == 1 or k < C[n-1][m-1]:
            if m == 1:
                word[ix:] = [1] * n
                word[ix+k-1] = 0
                break
            word[ix] = 0 # record the index of two_letters[0].
            ix += 1
            n -= 1   # length of the rest part of the word to find.
            m -= 1   # num of letters[0]

        # C(n-1,m-1) < k < C(n,m)
        # then the ix-th letter is two_letters[1],
        # and the k-th word is in the second part.
        # It's equivalent to find the (k - C(n-1,m-1))-th word
        # of length n-1, consisting of m two_letters[0]
        # and n-1-m two_letters[1].
        elif k > C[n-1][m-1]:
            word[ix] = 1 # recoder the index of two_letters[1]
            ix += 1 # move the ix to next pos.
            k -= C[n-1][m-1] # pos in the second part.
            n -= 1  # length of the rest part of the word to find.
        # k == C[n-1][m-1]
        # then this word of length n starts with two_letters[0]
        # and the rest of it is the last word of the dict of words of length
        # n-1 composing of m-1 two_letters[0] and n-(m-1) two_letters[1].
        else:
            word[ix] = 0
            word[ix+1:] = [1]*((n-1)-(m-1)) + [0]*(m-1)
            break
    word = [two_letters[ix] for ix in word]

    return word

def test():
    # letters = [0,1]
    letters = ['a','z']
    # n1,n2 = 2,3
    # n1,n2 = 3,3
    # n1,n2 = 5,3
    n1,n2 = 5,5
    print("the combinatorial number triangle:")
    C = combinatorial_number(n1+n2)
    for c in C: print(c)
    total = C[n1+n2][n1] # C(5,2)

    print("all words in the dict composing of:  %d '%s's and %d '%s's"\
        %(n1, str(letters[0]), n2, str(letters[1])))

    passed = True
    for k in range(1,total+1):
        w0 = the_kth_2_letter_word(letters,n1,n2,k,C)
        w1 = [letters[0]]*n1 + [letters[1]]*n2
        the_kth_one_in_permutation(w1,k)
        correct = (w0 == w1)
        print("%3d-th word: "%k, ''.join([str(l) for l in w0]), \
            " correct? ", correct)
        passed = passed and correct
    print('test_result: ', 'passed' if passed else "failed" )

if __name__ == '__main__':
    test()