
def solu(addens, s, record=None):
    """Compute the number of the combinitions of addens
       adding up to a sum recursively.
       === args ===  
       addens: a list of ascendingly sorted positive integers;
       s: the sum these addens should add up to.
       record: a dict to record the result already computed
            to avoid duplication in computation.
       return: the number of all possible combinitions.
    """
    # print('param:', s, addens)
    # print(record)
    if None == addens or None == s or 0 == len(addens) or s < addens[0]:
        return 0
    if s == addens[0]:
        return 1
    if None == record:
        record = {}
    else:
        assert isinstance(record,dict)
    if None != record.get((s,tuple(addens))):
        # print('got', s, addens, record.get((s,tuple(addens))))
        return record.get((s,tuple(addens)))
    cnt   = 0
    adden = 0
    while adden <= s:
        if adden < s:
            cnt += solu(addens[1:],s-adden,record)
        else: # adden == s
            cnt += 1
            break
        adden += addens[0]

    record[(s,tuple(addens))] = cnt
    return cnt


def combinatorial_num_of_addens(addens, s):
    """compute the combinatorial number of addens adding up to a sum s.
       === args ===
       addens: the addens to choose from to make a sum, each one can be chosen
               any times, 0, 1, 2, etc.;
       s: the sum these addens should add up to.
       return: the number of all possible combinitions.
    """
    assert None != addens
    assert len(addens) > 1
    assert all([x > 0 for x in addens])
    assert None != s

    fn = [0]*(addens[0]-1)
    addens = sorted(addens)
    inter_rslt = {}
    for i in range(addens[0],addens[-1]+1):
        cnt = solu(addens,i,inter_rslt)
        fn.append(cnt)
        # print('inter_rslt:', inter_rslt)
    print('addens:', addens)
    print('fn',fn,len(fn))
    for i in range(addens[-1]+1,s+1):
        cnt = 0
        for ix in addens:
            cnt += fn[i-ix-1]
        fn.append(cnt)
        # print(i,fn)
    for i in range(len(fn)):
        print("%d:%d"%(i+1,fn[i]))


def test():
    # addens = [1,2,5,10] # face value of RMB
    addens = [1,2] # Fabonacci sequence.
    combinatorial_num_of_addens(addens,23)


if __name__ == '__main__':
    test()