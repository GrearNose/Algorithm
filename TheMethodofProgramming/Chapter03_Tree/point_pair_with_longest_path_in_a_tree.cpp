#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <iostream>
#define DEPTH 5
using namespace std;

/*
Definition of node of an auxiliary tree to record the longest
path of a given tree.
*/
struct TreePathNode
{
    int depth_left, depth_right, len, come_from;
    TreePathNode *lchild, *rchild;
    TreePathNode(int dl, int dr, int l, int c)
    {
        depth_left  = dl;
        depth_right = dr;
        len         = l;
        come_from   = c;
        lchild      = rchild = NULL;
    }
};


/*
Simple definition of a tree node to show the algorithm.
*/
struct TreeNode
{
    int data;
    TreeNode *lchild, *rchild;
    TreeNode(int d)
    {
        data = d;
        lchild = rchild = NULL;
    }
};

/*
print the data field 'data' of a tree node.
*/
void print_node(TreeNode *node)
{
    cout << node->data << endl;
}

/*
Destroy a tree recursively.
*/
template <typename TreeNode>
void free_tree(TreeNode*&root)
{
    if(NULL == root)
        return;
    free_tree(root->lchild);
    free_tree(root->rchild);
    delete root;
    root = NULL; // Never forget to do this.
}

/*
print a node of TreePathNode.
*/
void print_tree_path_node(TreePathNode*node)
{
    if(node)
        printf("[%d,%d,%d,%d]\n", node->depth_left,\
          node->depth_right, node->len, node->come_from);
}


/*
Recursively print the nodes of a tree and its structure horizontally.
Args
root: root node of the tree;
print_func: the func to print each node of tree;
depth: current depth of the root;
branch: a bool array to record the branches to print;
item_width: output width of each node.
*/
template <typename TreeNode>
void print_tree(TreeNode *root, void (*print_func)(TreeNode*),\
                 int depth, bool branch[], int item_width = 3)
{
    if(NULL == root)
        return;
    for (int i = 0; i < depth; ++i)
    {
        char twig;
        if (i == depth - 1)
            twig = '-';
        else
            twig = ' ';

        if (branch[i])
            printf("|");
        else
            putchar(twig);

        for (int i = 0; i < item_width; ++i)
            putchar(twig);
    }

    print_func(root);

    if (root->rchild) // print the branch only when the tree has right children.
    {
        branch[depth] = true;
        print_tree(root->lchild, print_func, depth+1, branch);
        branch[depth] = false;
    }

    print_tree(root->rchild, print_func, depth+1, branch);
}

/*
Randomly generate a binary tree with the specified depth.
args
depth: max depth of the tree to generate;
cnt: counting of the node, used as the node data field;
reach_bottom: a flag showing if the tree has reached the max depth.
*/
TreeNode* generate_rand_binary_tree(int depth, int &cnt, bool &reach_bottom)
{
    if (depth < 0)
    {
        return NULL;
    }
    cnt += 1;
    TreeNode *root = new TreeNode(cnt);
    // randomly have children when reach_bottom is true,
    // i.e. leaf nodes at the maximum depth have been generated.
    if(!reach_bottom || rand() % 2)
    {
        root->lchild = generate_rand_binary_tree(depth-1, cnt, reach_bottom);
        root->rchild = generate_rand_binary_tree(depth-1, cnt, reach_bottom);
    }
    if(depth == 0)
        reach_bottom = true;
    return root;
}

/*
Target func to show the algorithm how to calculate the longest path in a binary
tree whose edges are treated as bidirectional.
Args
root: root of the tree;
depth: current depth of the root.
return
a binary tree with each node showing the longest path of a corresponding subtree,
and its structure is similar to the given tree, with some subtrees removed
if they cannot form part of the longest path.
*/
template <typename TreeNode>
TreePathNode* longest_path(TreeNode * root, int depth)
{
    if (root == NULL)
        return NULL;
    TreePathNode *d, *dl, *dr;
    // printf("node,depth:%d, %d\n", root->data, depth);
    d  = new TreePathNode(0,0,0,0);
    dl = longest_path(root->lchild, depth+1);
    dr = longest_path(root->rchild, depth+1);
    if(dl)
        d->depth_left  = 1 + max(dl->depth_left, dl->depth_right);
    if(dr)
        d->depth_right = 1 + max(dr->depth_left, dr->depth_right);
    d->len         = d->depth_left + d->depth_right;
    d->come_from   = 1;
    d->lchild      = dl;
    d->rchild      = dr;

    if (dl && d->len <= dl->len)
    {
        if (d->len < dl->len)
            d->come_from = 2;
        else
            d->come_from = 3;
        d->len = dl->len;
    }
    if (dr && d->len <= dr->len)
    {
        if(d->len < dr->len)
            d->come_from = 4;
        else
            d->come_from = 5;
        d->len = dr->len;
    }
    switch(d->come_from)
    {
        // the path is comprised of the max subpath from the lchild,
        // the root and the max subpath from rchild.
        case 1:
            // delete the grandchidren from his lchild.
            if (dl && d->lchild->depth_left > d->lchild->depth_right)
            {
                free_tree(d->lchild->rchild);
                assert(NULL == d->lchild->rchild);
            }
            else if (dl && d->lchild->depth_left < d->lchild->depth_right)
            {
                free_tree(d->lchild->lchild);
                assert(NULL == d->lchild->lchild);
            }
            // delete the grandchidren from his rchild.
            if (dr && d->rchild->depth_left > d->rchild->depth_right)
            {
                free_tree(d->rchild->rchild);
                assert(NULL == d->rchild->rchild);
            }
            else if (dr && d->rchild->depth_left < d->rchild->depth_right)
            {
                free_tree(d->rchild->lchild);
                assert(NULL == d->rchild->lchild);
            }
            break;
        // the max path is from lchild, so free delete rchild.
        case 2:
            free_tree(d->rchild);
            break;
        // the max path is from rchild, so free delete lchild.
        case 4:
            free_tree(d->lchild);
    }
    return d;
}


/*
Simply test the correctness of the algorithm.
*/
void test()
{
    int cnt = 0;
    bool reached = false, branch[DEPTH] = {false};
    srand(time(NULL));
    TreeNode *root = generate_rand_binary_tree(DEPTH, cnt, reached);
    cout << "the tree to search :" << endl;
    print_tree(root, print_node, 0, branch);

    TreePathNode * rootpath = longest_path(root,0);
    cout << "the result tree: [ldepth,rdepth,len,comefrom]" << endl;
    print_tree(rootpath, print_tree_path_node, 0, branch);
    free_tree(root);
    free_tree(rootpath);
    assert(root == NULL && rootpath == NULL);
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}