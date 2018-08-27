from time import time
from random import randint, seed

def stack_seq(stack, seq_in, seq_out, seq_cur=[]):
    if None == stack or None == seq_in or None == seq_out or None == seq_cur:
        return
    if 0 == len(seq_in): # can only pop
        seq_cur += stack[::-1] # pop all.
        seq_out.append(seq_cur)
    elif 0 == len(stack): # can only push
        stack.append(seq_in[0])
        stack_seq(stack, seq_in[1:], seq_out, seq_cur)
    else: # pop or push
        # pop
        seq_cur.append(stack[-1])
        stack_seq(stack[:-1], seq_in[:], seq_out, seq_cur[:])
        seq_cur.pop() # recover to the prev state.
        # push
        stack.append(seq_in[0])
        stack_seq(stack, seq_in[1:], seq_out, seq_cur)

def test():
    seq = [3,2,1,4]
    seq_in = [str(x) for x in seq]
    seq_out = []
    stack_seq([],seq_in,seq_out)
    seq_out.sort(key= lambda x: ''.join([str(i) for i in x]))
    for seq in seq_out:
        print(' '.join(seq))

if __name__ == '__main__':
    test()