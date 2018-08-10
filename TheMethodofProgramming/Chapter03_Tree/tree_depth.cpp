#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <iostream>
#define MAX_DEPTH 10
using namespace std;

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
Destroy a tree recursively.
*/
template <typename TreeNode>
void free_tree(TreeNode*&root, int mxDepth = 1)
{
    if(NULL == root)
        return;
    free_tree(root->lchild, mxDepth-1);
    free_tree(root->rchild,mxDepth-1);
    delete root;
    root = NULL; // Never forget to do this.
}

/*
print the data field 'data' of a tree node.
*/
void  print_node(TreeNode *node)
{
    cout << node->data << endl;
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
void print_tree_horizontally(TreeNode *root, void (*print_func)(TreeNode*),\
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
        return NULL;
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
Target func to show the algorithm how to calculate the max depth
 of a binary tree.
Args
root: root of the tree;
depth: current depth of the root;
mxDepth: a var to record the max depth found during the traversal.
*/
template <typename TreeNode>
void tree_depth(TreeNode * root, int depth, int &mxDepth)
{
    if (NULL == root)
        return;
    if (depth > mxDepth)
        mxDepth = depth;
    tree_depth(root->lchild, depth+1, mxDepth);
    tree_depth(root->rchild, depth+1, mxDepth);
}


/*
Simply test the correctness of the algorithm.
*/
void test()
{
    int cnt = 0, depth = 0, mxDepth = 0;
    bool reached = false, *branch;
    srand(time(NULL));
    while(!depth)
        depth = rand() % MAX_DEPTH;
    branch = new bool[depth];

    TreeNode *root = generate_rand_binary_tree(depth, cnt, reached);
    cout << "the tree to search :" << endl;
    print_tree(root, print_node, 0, branch);

    tree_depth(root,0,mxDepth);
    cout << "max depth of the tree:" << mxDepth << endl;
    if (mxDepth == depth)
        cout << "Correct !" << endl;
    else
        cout << "Wrong!\nReal depth: " << depth << endl;

    free_tree(root);
    assert(root == NULL);
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}