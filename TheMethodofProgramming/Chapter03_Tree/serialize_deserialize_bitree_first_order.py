class Node:
    """ definition of a node of a binary tree."""
    def __init__(self,d):
      self.data = d
      self.left   = None
      self.right = None

def print_tree_horizontally(root, depth=0, isleft=None):
    """ Print a binary tree layer by layer horizontally.
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
    # else:
    #     print('rt:', end='')

    print(root.data)
    print_tree_horizontally(root.left,depth+1, True)
    print_tree_horizontally(root.right,depth+1,False)

def serialize_bitree_first_order(root):
    """Serialze a binary tree into a string in first order,
       using '!' as separator and '#' for None node."""
    if None == root:
        return "#!"
    s = str(root.data) + "!"
    if None == root.left:
        s += "#!"
    else:
        s += serialize_bitree_first_order(root.left)
    if None == root.right:
        s += "#!"
    else:
        s += serialize_bitree_first_order(root.right)
    return s

def deserialze_bitree_first_order(s):
    ix = s.index('!')
    d,s = s[:ix],s[ix+1:]
    if d == '#':
        return None, s

    data = int(d)
    root = Node(data)
    # N.B. s will be modified during this call.
    root.left,s  = deserialze_bitree_first_order(s)
    root.right,s = deserialze_bitree_first_order(s)
    return root,s

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
    root.left  = reconstruct_tree_first_in(left)
    root.right = reconstruct_tree_first_in(right)
    return root

def test():
    first_order = [1,2,4,7,3,5,6,8]
    last_order  = [7,4,2,5,8,6,3,1]
    in_order    = [4,7,2,1,5,3,8,6]

    tree = reconstruct_tree_first_in([first_order,in_order])
    print('The original tree:')
    print_tree_horizontally(tree)
    s = serialize_bitree_first_order(tree)
    print('serialized str: ', s)
    tree2,_ = deserialze_bitree_first_order(s)
    print('construct the bitree by deserialzing the str:')
    print_tree_horizontally(tree2)

    s = '12!3!#!#!#!'
    print('another test data for deserialze_bitree_first_order: ', s)
    tree3,_ = deserialze_bitree_first_order(s)
    print('the tree:')
    print_tree_horizontally(tree3)
    print('Done!')

if __name__ == '__main__':
    test()