
def edit_dis(s,t):
    if None == s or None == t:
        return None
    if 0 == len(s):
        return len(t)
    if 0 == len(t):
        return len(s)
    if s[-1] == t[-1]:
        return edit_dis(s[:-1],t[:-1])
    else:
        # del s[-1], convert t into s[:-1]
        d1 = edit_dis(s[:-1],t)
        # del t[-1], convert s into t[:-1]
        d2 = edit_dis(s,t[:-1])
        # change s[-1] into t[-1], then convert s[:-1] into t[:-1]
        d3 = edit_dis(s[:-1],t[:-1])
        return 1 + min(d1,d2,d3)

def edit_dis_v2(s,t,debug=False):
    if len(s) < len(t):
        s,t = t,s
    cur = [0]*(len(t)+1)
    prev = list(range(len(t)+1)) # when s's length is 0.
    if debug:
        print('      ',end='')
        for c in t[:-1]: print(c,end='  ')
    if debug: print(t[-1])
    if debug: print(' ', prev)
    for i in range(1,len(s)+1):
        cur[0] = i
        for j in range(1,len(t)+1):
            if s[i-1] == t[j-1]:
                cur[j] = prev[j-1]
            else:
                cur[j] = 1 + min(prev[j-1],prev[j],cur[j-1])
        prev,cur = cur,prev
        if debug: print(s[i-1],prev)
    # print(prev[-1])
    return prev[-1]

def test():
    s = 'abcdef'
    t = 'abcfafe'
    print(s)
    print(t)
    print('edit distance:', edit_dis(s,t), 'vs', edit_dis_v2(s,t))

if __name__ == '__main__':
    test()
