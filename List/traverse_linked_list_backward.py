class ListNode:
    """simple definition of the list node"""
    def __init__(self, data):
        self.data = data
        self.next = None

def traverse(node):
    print(node.data, end=" ")

def traverse_linked_list_backward(linked_list,traverse_func):
    """
        visit the linked list backward.
    """
    if None == linked_list:
        return
    stack = []
    cur   = linked_list
    while None != cur:
        stack.append(cur)
        cur = cur.next
    # print([x.data for x in stack])
    while len(stack) > 0:
        node = stack.pop()
        traverse_func(node)

def test():
    ln   = 13
    head = None
    prev = None
    for i in range(ln):
        cur = ListNode(i)
        if None == head:
            head = cur
            prev = cur
        else:
            prev.next = cur
        prev = cur

    print("the linked list: ")
    cur = head
    while cur:
        print(cur.data, end=" ")
        cur = cur.next
    print()
    print('Traversing backward:')
    traverse_linked_list_backward(head,traverse)
    print()

if __name__ == '__main__':
    test()
