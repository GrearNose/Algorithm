class QueueTwoStacks:
    """A queue implemented by using two stacks."""
    def __init__(self):
        self.stack_push = []
        self.stack_pop  = []
        self.len        = 0
    def enqueue(self,data):
        self.stack_push.append(data)
        self.len += 1

    def dequeue(self):
        if self.len <= 0:
            raise Exception("Queue empty!")
        if len(self.stack_pop)>0:
            data = self.stack_pop.pop()
        else:                
            while len(self.stack_push) > 0:
                self.stack_pop.append(self.stack_push.pop())
            data = self.stack_pop.pop()
        self.len -= 1
        return data

    def __len__(self):
        return self.len

def test():
    d1  = [1,2,3]
    d2  = [7,8,9]
    que = QueueTwoStacks()
    print('data for the que:', d1, d2)
    for d in d1: que.enqueue(d)
    print('enqueued the first load, now queue len:', len(que))
    print('pop one from the que:', que.dequeue())
    print('now queue len:', len(que))
    for d in d2: que.enqueue(d)
    print('enqueued the second load, now try to dequeue them all:')
    while len(que) > 0:
        print(que.dequeue(),end=" ")
    print()

if __name__ == '__main__':
    test()
