
def get_next(p):
    assert isinstance(p, str),'s,p should be str'
    if len(p) == 0: return None
    next_pos = [0] * len(p)
    i,j = 1,0
    while i < len(p):
        if p[i] == p[j]:
            i += 1
            j += 1
            next_pos[i] = j
        else:
            j = next_pos[j]

def str_find(s,p):
    assert isinstance(s, str) and isinstance(p, str),'s,p should be str'
    if len(s) == 0 or len(p) == 0 or len(s) < len(p):
        return None # not found
    next_pos = get_next(p)
    i,j = 0,0
    while i < len(s) and j < len(p):
        if s[i] == p[j]:
            i += 1
            j += 1
        else:
            j = next_pos[j]
    if j == len(p):
        return i - len(p)
    else:
        return None