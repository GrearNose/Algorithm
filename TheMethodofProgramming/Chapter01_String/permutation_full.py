from collections import Iterable
from itertools import permutations

class DigitLikeArrangement(object):
    """Generate all possible arrangement of the elems from
    the given set, each with a length of size of the given set,
    that's, just like all the n-digit numbers constructed from n
    different digits. An alternative algorithm is to use the conversing
    of number system. There are n^n arrangements. e.g. for '12', then
    its all arrnagements are: 11, 12, 21, 22. """
    def __init__(self,iterable):
        assert isinstance(iterable, Iterable)
        self.iterable = iterable
        self.ix       = [0]* len(iterable)
        self.max_ix   = len(iterable)-1

    def __iter__(self):
        return self

    def next(self): # for python3.3 or lower.
    # def __next__(self):
        within = [self.ix[i]<=self.max_ix for i in range(len(self.iterable))]
        if not all(within):
            raise StopIteration
        perm = [self.iterable[i] for i in self.ix]
        # update the indices.
        for i in reversed(range(len(self.iterable))):
            self.ix[i] += 1
            if self.ix[i]>self.max_ix and i>0:
                self.ix[i] = 0 # carry to the next bit.
            else:
                break
        return perm


def full_permut_once_all(l):
    """A recursive func to generate the full permutation."""
    if len(l) == 1:
        return l
    else:
        perms = []
        for i in range(len(l)):
            cur = l[i]
            rest= l[:i] + l[i+1:]
            sub = full_permut_once_all(rest)
            # print('cur,rest,sub:',cur,rest,sub)
            cur_set = [[cur]+s for s in (sub if isinstance(sub[0],list) else [sub])]
            perms.append(cur_set)
        return perms


def test():
    l   = [1,2,3]
    it1 = DigitLikeArrangement(l)
    it2 = permutations(l)
    print('is iterable:', isinstance(it1,Iterable))
    for i in it1:
        print(i)
    # for (i,(p1,p2)) in enumerate(zip(it1,it2)):
    #     print(i,p1,p2)

    s = full_permut_once_all(l)
    for i in s:
        print(i)

if __name__ == '__main__':
    test()