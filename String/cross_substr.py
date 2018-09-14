def cross_substr_v0(s1,s2,s3):
    assert all([None != s for s in [s1,s2,s3]])
    if len(s1) + len(s2) != len(s3):
        return False
    # use a matrix to record the result,
    # dp[i][j] =
    #  True if s3[:i+j] consists of cross all substrs
    #       of s1[:i] and s2[:j]; that is, 
    #       either s1[i-1] == s3[i+j-1] and dp[i-1][j] == True,
    #       or s2[j-1] == s3[i+j-1] and dp[i][j-1] == True
    # False otherwise.
    # 
    dp = []
    for _ in range(len(s1)+1):
        dp.append([0]*(1+len(s2)))
    dp[0][0] = 1 # true when s1,s2,s3 are empty string.
    for i in range(1+len(s1)):
        for j in range(1+len(s2)):
            # mind that for the first row of dp, it means s1 is empty.
            if dp[i][j] or \
                (i>0 and dp[i-1][j] and s3[i+j-1] == s1[i-1]) \
                or (j>0 and dp[i][j-1] and s3[i+j-1] == s2[j-1]):
                dp[i][j] = 1
            else:
                dp[i][j] = 0
    for r in dp:
        print(r)
    return dp[-1][-1]

def cross_substr(s1,s2,s3,debug=False):
    assert all([None != s for s in [s1,s2,s3]])
    if len(s1) + len(s2) != len(s3):
        return False
    if len(s1) < len(s2):
        s1,s2 = s2,s1
    cur = [0]*(1+len(s2))
    pre = [1] + [1 if s2[i] == s3[i] else 0 for i in range(len(s2))]
    pre[0] = cur[0] = 1 # true when s1,s2,s3 are empty string.
    if debug: print(pre)
    for i in range(1,len(s1)+1):
        for j in range(1,len(s2)+1):
            if (pre[j] and s3[i+j-1] == s1[i-1]) \
                or (cur[j-1] and s3[i+j-1] == s2[j-1]):
                cur[j] = 1
            else:
                cur[j] = 0
        if debug: print(cur)
        pre,cur = cur,pre
    return pre[-1]

def test():
    # s1,s2,s3 = '123512,123412,123512314212'
    # s1,s2,s3 = '123412,123512,123125312412'.split(',')
    s1,s2,s3 = 'a,b,ab'.split(',')
    print(s1,s2,s3)
    # print(cross_substr_v0(s1,s2,s3))
    print(cross_substr(s1,s2,s3))

if __name__ == '__main__':
    test()