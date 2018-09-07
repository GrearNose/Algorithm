from collections import Iterable

def the_first_elem_appear_once(iterable):
    if None == iterable or not isinstance(iterable, Iterable):
        return None
    keys = []
    occurence = []
    for e in iterable:
        if e not in keys:
            keys.append(e)
            occurence.append(1)
        else:
            ix = keys.index(e)
            occurence[ix] += 1
    if 1 in occurence:
        ix = occurence.index(1)
        return keys[ix]
    else:
        return None

def test():
    s = 'asdgjasfjdasdf3nsadlfj'
    # s = '111k1223232334'
    # s = '1111223232334'
    # s = 'a1111223232334'
    # s = '11112232323344'
    # s = ''
    # s = '123'
    # s = [1,2,3]
    # s = {2,3,4,4,2}
    # s = {2:34,'aw':23}
    print('s:', s)
    print(the_first_elem_appear_once(s))

if __name__ == '__main__':
    test()