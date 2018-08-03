
maxn = 100
wa,wb,wv,ws = [0]*maxn,[0]*maxn,[0]*maxn,[0]*maxn

def cmp(r,a,b,l):
    return r[a] == r[b] and r[a+l] == r[b+l]

def da(r,sa,n,m):
    ws = [0]*m
    x,y = wa,wb
    for i in range(n):
        x[i]= r[i]
        ws[r[i]] += 1
    for i in range(1,m):
        ws[i] += ws[i-1]
    for i in reversed(range(n)):
        ws[x[i]] -= 1
        ix = ws[x[i]]
        sa[ix] = i
    j = 1
    for p in range(1,n):
        for 
