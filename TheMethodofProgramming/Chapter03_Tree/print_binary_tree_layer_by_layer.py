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
    else:
        print('rt:', end='')

    print(root.data)
    print_tree_horizontally(root.left,depth+1, True)
    print_tree_horizontally(root.right,depth+1,False)


def print_tree_vertically(root):
    """Print a binary tree layer by layer vertically."""
    que = []
    last, nlast = root,root
    que.append(root)
    while(len(que) > 0):
        p = que[0]
        del que[0]
        print(p.data,end=' ')
        if p.left:
            nlast = p.left
            que.append(nlast)
        if p.right:
            nlast = p.right
            que.append(nlast)
        if p == last:
            print()
            last = nlast

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
    print('tree1 contructed from first and in order traversal sequence:')
    print_tree_horizontally(tree)
    print_tree_vertically(tree)

    print('Done!')

if __name__ == '__main__':
    test()