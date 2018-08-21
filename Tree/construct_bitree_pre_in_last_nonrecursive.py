class TreeNode:
    """ definition of a node of a binary tree."""
    def __init__(self,d):
      self.data   = d
      self.lchild = None
      self.rchild = None


def print_tree_horizontally(root, depth=0, isleft=None):
    """ Print a binary tree. 
        === Args ===
        root:   the root node of the binary tree;
        depth:  the depth of current node;
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


def construct_bitree_pre_in(pre_seq, in_seq):
    """Construct a binary tree from preorder traversal sequence
       and in-order traversal sequence, nonrecursively.
       ===Args===
       pre_seq   the pre-order traversal sequence;
       in_seq    the in-order traversal sequence.
       return    the root node of the bitree.
    """
    if None == pre_seq:
        return None
    assert len(pre_seq) == len(in_seq)

    # beginning index of the subsequence of in_seq
    # corresponding to the current subtree.
    ix_b      = 0
    # ending index of the subsequence of in_seq
    # corresponding to the current subtree.
    ix_e      = len(in_seq)-1
    # whether the curent node is the lchild of its parent (if it has).
    is_lchild = None
    # parent of current node.
    parent    = None
    # used to record the parent-child relationship.
    stack     = [(ix_b,ix_e,is_lchild,parent)]

    # construct the whole bitree by fetching nodes from pre_seq
    # and connecting children to the parent using the position
    # offered by in_seq.
    for data in pre_seq:
        ix_b, ix_e, is_lchild, parent = stack.pop()
        # ix_cur = ix_b + in_seq[ix_b:ix_e+1].index(data)
        ix_cur = in_seq.index(data)
        root   = TreeNode(data)

        # record current node as the root of the whole tree.
        if None == parent:
            tree_root = root
        # connect current node to its parent.
        else:
            if is_lchild:
                parent.lchild = root
            else:
                parent.rchild = root

        if ix_cur < ix_e:      # rchild exits, push its info.
            rd = (ix_cur+1,ix_e,False,root)
            stack.append(rd)
        if ix_b < ix_cur:      # lchild exists, push its info.
            rd = (ix_b,ix_cur-1,True,root)
            stack.append(rd)

    return tree_root


def construct_bitree_last_in(last_seq, in_seq):
    """
        construct a binary tree from last order traversal sequence
        and in-order traversal sequece.
        === Args ===
        last_seq  the last-order traversal sequence;
        in_seq    the in-order traversal sequence.
        return    the root of the whole tree.
    """
    if None == last_seq:
        return None
    assert len(last_seq) == len(in_seq)

    # beginning index of the subsequence of in_seq
    # corresponding to the current subtree.
    ix_b      = 0
    # ending index of the subsequence of in_seq
    # corresponding to the current subtree.
    ix_e      = len(in_seq)-1
    # whether the curent node is the lchild of its parent (if it has).
    is_lchild = None
    # parent of current node.
    parent    = None
    # used to record the parent-child relationship.
    stack     = [(ix_b,ix_e,is_lchild,parent)]

    # contruct the bitree by fetching nodes from last-order traversal sequence
    # and connecting the children to their parents using the parent-child info
    # offering by in_seq.
    for data in last_seq[::-1]: # reversed order, construct from the last one.
        ix_b,ix_e,is_lchild,parent = stack.pop()
        ix_cur = in_seq.index(data)
        root   = TreeNode(data)

        # record current node as the root as the whole tree.
        if None == parent:
            tree_root = root
        # connect current node to its parent
        else:
            if is_lchild:
                parent.lchild = root
            else:
                parent.rchild = root
        if ix_b < ix_cur:
            rd = (ix_b,ix_cur-1,True,root)
            stack.append(rd)
        if ix_cur < ix_e:
            rd = (ix_cur+1,ix_e,False,root)
            stack.append(rd)

    return tree_root


def test():
    first_order = [1,2,4,7,3,5,6,8]
    last_order  = [7,4,2,5,8,6,3,1]
    in_order    = [4,7,2,1,5,3,8,6]

    print('pre: ', first_order)
    print('in:  ', in_order)
    print('last:', last_order)
    tree1 = construct_bitree_pre_in(first_order,in_order)
    print('tree1 contructed from first and in order traversal sequence:')
    print_tree_horizontally(tree1)

    tree2 = construct_bitree_last_in(last_order,in_order)
    print('tree2 contructed from last and in order traversal sequence:')
    print_tree_horizontally(tree2)

    print('Done!')

if __name__ == '__main__':
    test()