def str_left_shift_one(s):
    t = s[0]
    for i in range(len(s)-1):
        s[i] = s[i+1]
    s[-1] = t
if __name__ == '__main__':
    s='I am a student'
    str_left_shift_one(s)
    print(s)