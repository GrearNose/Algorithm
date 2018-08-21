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


def test():
    first_order = [1,2,4,7,3,5,6,8]
    last_order  = [7,4,2,5,8,6,3,1]
    in_order    = [4,7,2,1,5,3,8,6]

    tree1 = reconstruct_tree_first_in([first_order,in_order])
    print('tree1 contructed from first and in order traversal sequence:')
    print_tree_horizontally(tree1)

    tree2 = reconstruct_tree_last_in([last_order,in_order])
    print('tree2 contructed from last and in order traversal sequence:')
    print_tree_horizontally(tree2)

    print('Done!')

if __name__ == '__main__':
    test()