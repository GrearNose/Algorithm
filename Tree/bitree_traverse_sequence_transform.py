class Node:
    """ definition of a node of a binary tree."""
    def __init__(self,d):
      self.data   = d
      self.lchild = None
      self.rchild = None

def print_tree_horizontally(root, depth=0, isleft=None):
    """ Print a binary tree. 
        root: the root node of the binary tree;
        depth: the depth of current node;
        isleft: a flag indicating the current root
            is a root if it's None, left child if True,
            and right child if False.
    """
    if not root: return
    for _ in range(depth):
      # print('   ', end='')
      print('   ', end='')
    if True == isleft:
        print('l:', end='')
    elif False == isleft:
        print('r:', end='')
    else:
        print('rt:', end='')

    print(root.data)
    print_tree_horizontally(root.lchild,depth+1, True)
    print_tree_horizontally(root.rchild,depth+1,False)


def reconstruct_tree_first_in(FirstAndIn):
    """reconstruct a binary tree from first and in order traversal sequences."""
    if 0 == len(FirstAndIn[0]): return
    First,In = FirstAndIn
    # print('first, in', First, In)
    # the first node in first order traversal sequence is the root.
    d          = First[0]
    ix         = In.index(d)
    left       = (First[1:ix+1], In[:ix])  # lchild subtree
    right      = (First[ix+1:], In[ix+1:]) # rchild subtree
    root       = Node(d)
    root.lchild= reconstruct_tree_first_in(left)
    root.rchild= reconstruct_tree_first_in(right)
    return root

def reconstruct_tree_last_in(LastAndIn):
    """reconstruct a binary tree from last and in order traversal sequences."""
    if 0 == len(LastAndIn[0]): return None
    Last,In = LastAndIn
    # print('last, in', Last, In)
    # the last node in last order traversal sequence is the root.
    d          = Last[-1]
    ix         = In.index(d)
    left       = (Last[:ix], In[:ix])      # lchild subtree
    right      = (Last[ix:-1], In[ix+1:])  # rchild subtree
    root       = Node(d)
    root.lchild= reconstruct_tree_last_in(left)
    root.rchild= reconstruct_tree_last_in(right)
    return root

def pre_traverse(root,traverse_record):
    if not isinstance(root, Node):
        return
    assert isinstance(traverse_record, list)
    traverse_record.append(root.data)
    pre_traverse(root.lchild, traverse_record)
    pre_traverse(root.rchild, traverse_record)

def last_traverse(root,traverse_record):
    if not isinstance(root, Node):
        return
    assert isinstance(traverse_record, list)
    if root.lchild:
        last_traverse(root.lchild, traverse_record)
    if root.rchild:
        last_traverse(root.rchild, traverse_record)
    traverse_record.append(root.data)


def convert_first_in_to_last_order(first_order,in_order):
    """
        Converse the first and in bitree traversal order 
        nto last traversal order.
    """
    if None == first_order or None == in_order\
        or len(first_order) != len(in_order):
        return None

    tree1 = reconstruct_tree_first_in([first_order,in_order])
    # print('tree1 contructed from first and in order traversal sequence:')
    # print_tree_horizontally(tree1)
    last = []
    last_traverse(tree1,last)
    return last

def convert_last_in_to_first_order(last_order,in_order):
    """
        Converse the last and in bitree traversal order
        into last traversal order.
    """
    if None == last_order or None == in_order\
        or len(last_order) != len(in_order):
        return None

    tree = reconstruct_tree_last_in([last_order,in_order])
    # print('tree contructed from last and in order traversal sequence:')
    # print_tree_horizontally(tree)
    first  = []
    pre_traverse(tree,first)
    return first

def test():
    first_order = [1,2,4,7,3,5,6,8]
    last_order  = [7,4,2,5,8,6,3,1]
    in_order    = [4,7,2,1,5,3,8,6]
    print('first_order', first_order)
    print('last_order ', last_order)
    print('in_order   ', in_order)

    last  = convert_first_in_to_last_order(first_order,in_order)
    first = convert_last_in_to_first_order(last_order,in_order)

    print('last_order ', last)
    print('first_order',first)

if __name__ == '__main__':
    test()