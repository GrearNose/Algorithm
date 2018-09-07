import traceback
try:
    while True:
        nums = [int(x) for x in input().split()]
        n    = len(nums)
        mx   = [0]*n
        for i in range(1,n):
            mx[0] = nums[0]
            for j in range(i):
                if nums[i] > nums[j]:
                    mx[i] = max(mx[i], mx[j]+nums[i])
            mx[i] = max(mx[i], nums[i]);
        print(max(mx))

except EOFError:
    pass
except Exception as e:
    traceback.print_exc(e)