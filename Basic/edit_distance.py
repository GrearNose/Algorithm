import traceback
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
        d1 = edit_dis(s[:-1],t)
        d2 = edit_dis(s,t[:-1])
        d3 = edit_dis(s[:-1],t[:-1])
        return min(d1,d2,d3)
try:
    while True:
        s = input()
        t = input()
        if len(s) < len(t):
            s,t = t,s
        cur = [0]*(len(t)+1)
        prev = list(range(len(t)+1)) # when s's length is 0.
        print('      ',end='')
        for c in t[:-1]: print(c,end='  ')
        print(t[-1])
        print(' ', prev)
        for i in range(1,len(s)+1):
            cur[0] = i
            for j in range(1,len(t)+1):
                if s[i-1] == t[j-1]:
                    cur[j] = prev[j-1]
                else:
                    cur[j] = 1 + min(prev[j-1],prev[j],cur[j-1])
            prev,cur = cur,prev
            print(s[i-1],prev)
        print(prev[-1])
except EOFError:
    pass
except Exception as e:
    traceback.print_exc(e)