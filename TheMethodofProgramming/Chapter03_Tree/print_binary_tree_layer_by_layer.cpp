#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <queue>
#include <iostream>
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
        print_tree_horizontal(root->lchild, print_func, depth+1, branch);
        branch[depth] = false;
    }

    print_tree_horizontal(root->rchild, print_func, depth+1, branch);
}


/*
Print a tree layer by layer vertically using a queue, using two pointer
last and nlast. last points to the last node of the current layer to print,
while nlast points to the last node pushed into the queue. Each time pop
a node and print its info, and if it equals to last, print a new line and
update last with nlast.
Args
root: pointer to the root of the tree to print.
*/
template <typename TreeNode>
void print_tree_vertically(TreeNode *root)
{
    queue<TreeNode*> que;
    TreeNode *last, *nlast, *p;
    last = nlast = root;
    que.push(root);
    do
    {
        p = que.front();
        que.pop();
        cout << p->data << " ";
        if (p->lchild)
        {
            nlast = p->lchild;
            que.push(nlast);
        }
        if (p->rchild)
        {
            nlast = p->rchild;
            que.push(nlast);
        }
        if (p == last)
        {
            cout << endl;
            last = nlast;
        }
    }while(!que.empty());
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
Simply test the correctness of the algorithm.
*/
void test()
{
    int cnt = 0, depth = 0, mxDepth = 7;
    bool reached = false, *branch;
    srand(time(NULL));
    while(!depth)
        depth = rand() % mxDepth;
    branch = new bool[depth];

    TreeNode *root = generate_rand_binary_tree(depth, cnt, reached);
    cout << "the horizontal tree :" << endl;
    print_tree_horizontal(root, print_node, 0, branch);
    cout << "the vertical tree :" << endl;
    print_tree_vertical(root);

    free_tree(root);
    assert(root == NULL);
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}