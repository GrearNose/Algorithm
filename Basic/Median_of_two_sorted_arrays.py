def median(A, B):
    m, n = len(A), len(B)
    if m > n:
        A, B, m, n = B, A, n, m
    if n == 0: # ensure non-empty.
        raise ValueError

    imin, imax, half_len = 0, m, (m + n + 1) // 2
    while imin <= imax:
        i = (imin + imax) // 2
        j = half_len - i
        # print(i,j)
        # j will always positive since len(B) >= len(A)
        if   i < m and B[j-1] > A[i]: # i is too small, must increase it
            imin = i + 1
        elif i > 0 and A[i-1] > B[j]: # i is too big,   must decrease it
            imax = i - 1
        else: # i is perfect
            if   i == 0: max_of_left = B[j-1]
            elif j == 0: max_of_left = A[i-1]
            else:        max_of_left = max(A[i-1], B[j-1])

            if (m + n) % 2 == 1:
                return max_of_left

            if   i == m: min_of_right = B[j]
            elif j == n: min_of_right = A[i]
            else:        min_of_right = min(A[i], B[j])

            return (max_of_left + min_of_right) / 2.0

def main():
    x = range(1,21)
    y = range(20,26)
    print('the median of 1..25 is %d'%(median(x,y)))

if __name__ == '__main__':
    main()