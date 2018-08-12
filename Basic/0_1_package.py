
def package_0_1(n,C,W,V):
    # m[i,j], max value with items 1...i, and package with capacity j
    m = []
    for i in range(n): m.append([0]*(C+1))
    for j in range(W[0],C+1): m[0][j] = V[0]
    for i in range(1,n):
        for j in range(1,C+1):
            if W[i] <= j:
                m[i][j] = max(m[i-1][j], m[i-1][j-W[i]]+V[i])
            else:
                m[i][j] = m[i-1][j]
    return m

def knap_traceback(m,n,C,W,V):
    i, j, items = n-1, C, []
    while i>=0 and j>0:
        if m[i][j] == 0:
            break
        elif m[i][j] == m[i-1][j]:
            i = i-1
        else:
            # assert m[i][j] == m[i-1][j-W[i]] + V[i] or m[i][j] == V[0]
            items.append(i)
            j -= W[i]
            i = i-1
    return items

if __name__ == '__main__':
    # s = input().strip().split()
    # n,C = int(s[0]),int(s[1])
    # W = [int(x) for x in input().strip().split()] # weights
    # V = [int(x) for x in input().strip().split()] # values
    n,C = 5,10
    W = [2,2,6,5,4]
    V = [6,3,5,4,6]
    m = package_0_1(n,C,W,V)
    selected_items = knap_traceback(m,n,C,W,V)

    print('value matrix:')
    print('i\\W',[i for i in range(C+1)])
    for i,r in enumerate(m): print([i],r)

    print('selected items:', selected_items)