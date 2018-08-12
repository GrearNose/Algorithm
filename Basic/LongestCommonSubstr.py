
def longest_common_substr_brute_force(s,t):
    ix_s,mx_len = 0,0
    for i in range(len(s)):
        for j in range(len(t)):
            k = 0
            while k < min(len(s)-i,len(t)-j):
                if s[i+k] != t[j+k]: break
                k += 1
            if k > mx_len:
                ix_s,mx_len = i,k
    return s[ix_s:ix_s+mx_len]

def longest_common_substr_record(s,t):
    """
    As there are many repeated computation in brute-force version,
    using a table for recording can avoid this.
    m[i,j] records the max len of the common substr ending with s[i] and t[j],
    i.e. m[i,j] = m[i-1,j-1] + 1 if s[i]==t[j] else 0
    """
    ix_s,mx_len,m = 0,0,[]
    for i in range(len(s)):
        m.append([0]*len(t))
    for j in range(len(t)):
        m[0][j] = 1 if s[0] == t[j] else 0
        if m[0][j] > mx_len:
            ix_s,mx_len = j,1
    for i in range(1,len(s)):
        m[i][0] = 1 if s[i] == t[0] else 0
        for j in range(1,len(t)):
            if s[i] == t[j]:
                m[i][j] = m[i-1][j-1] + 1
            if m[i][j] > mx_len:
                ix_s,mx_len = i-m[i][j]+1, m[i][j]
    return s[ix_s:ix_s+mx_len]

def longest_common_substr_record_min_memory(s,t):
    """
    When filling the table m row by row, it's easy to find that
    only the last row is used to fill the current row. Thus
    all the previos row can be discarded.
    """
    if len(s) < len(t): s,t = t,s   # swap to ensure s is longer.
    pre,cur = [0]*len(t),[0]*len(t) # previous and current row.
    ix_s,mx_len = 0,0
    for j in range(len(t)):
        cur[j] = 1 if s[0]==t[j] else 0
        if cur[j] > mx_len:
            ix_s,mx_len = j, 1
    # Used alternately, 'cur' will become pre, while info in 'pre' will be dicard
    # and 'pre' will be reused (overwritten) as cur , thus swap them.
    pre,cur = cur, pre
    for i in range(1,len(s)):
        cur[0] = 1 if s[i]==t[j] else 0
        for j in range(1,len(t)):
            cur[j] = pre[j-1]+1 if s[i]==t[j] else 0
            if cur[j] > mx_len:
                ix_s, mx_len = i-cur[j]+1, cur[j]
        pre,cur = cur,pre
    return s[ix_s:ix_s+mx_len]

def longest_common_substr_diagonal_search(s,t):
    """
    Instead of filling the table row by row, filling by diagnoal line can
    further reduce the memory use to only one variable of previous state,
    as the value of m[i,j] only depends on m[i-1,j-1] when s[i]==t[j].
    """
    ix_s,mx_len = 0,0
    for k in range(max(len(s),len(t))):
        len1,len2 = 0,0
        for j in range(min(len(s)-k,len(t))): # fill the lower triangle of the table,m[k+j,j]
            len1 = len1+1 if s[k+j]==t[j] else 0
            if len1 > mx_len:
                ix_s,mx_len = k+j-len1+1,len1
        # N.B. the main diagonal will be filled twice, but never mind.
        for j in range(min(len(s),len(t)-k)): # fill the upper triangle of the table,m[j,k+j]
            len2 = len2+1 if t[k+j]==s[j] else 0
            if len2 > mx_len:
                ix_s,mx_len = j-len2+1,len2
    return s[ix_s:ix_s+mx_len]

if __name__ == '__main__':
    # s,t = input().strip(), input().strip()

    # s,t = 'abcdefg23589askdhase23r', '1(*%_23589alutaawiepg'
    # t,s = 'abcdefg23589askdhase23r', '1(*%_23589alutaawiepg'
    # s,t = 'dfgsa','d32059'
    # t,s = 'dfgsa','d32059'
    # s,t = '0abc','1abc'
    # s,t = 'abc3457','abc0976808'
    t,s = 'abc3457','abc0976808'

    print('s:',s,'\nt:',t)
    print('longest common substr:', longest_common_substr_brute_force(s,t))
    print('longest common substr:', longest_common_substr_record(s,t))
    print('longest common substr:', longest_common_substr_record_min_memory(s,t))
    print('longest common substr:', longest_common_substr_diagonal_search(s,t))