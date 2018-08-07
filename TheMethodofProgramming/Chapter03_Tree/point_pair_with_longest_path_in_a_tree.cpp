#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <iostream>
#define DEPTH 5
using namespace std;

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


template <typename TreeNode>
void free_tree(TreeNode**root, int mxDepth = 1)
{
    // if(NULL == root || NULL == *root || mxDepth == 0)
    if(NULL == root || NULL == *root)
        return;
    // cout << "about to deleting..." << endl;
    free_tree(&((*root)->lchild), mxDepth-1);
    free_tree(&((*root)->rchild),mxDepth-1);
    delete(*root);
    // cout << "deleted" << endl;
    *root = NULL; // Never forget to do this.
}


void print_tree_path_node(TreePathNode*node)
{
    if(node)
        printf("[%d,%d,%d,%d]\n", node->depth_left,\
          node->depth_right, node->len, node->come_from);
}


template <typename TreeNode>
void print_tree(TreeNode *root, void (*print_func)(TreeNode*),\
                 int depth, bool branch[], int item_width = 3)
{
    if(NULL == root)
        return;
    for (int i = 0; i < depth; ++i)
    {
        if (branch[i])
            printf("|");
        else if (i == depth-1)
            putchar('-');
        else
            putchar(' ');
        if (i == depth - 1)
        {
            for (int i = 0; i < item_width-1; ++i)
                putchar('-');
        }
        else
        {
            for (int i = 0; i < item_width-1; ++i)
                putchar(' ');
        }
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
    bool have_children = !reach_bottom || rand() % 2;
    if(have_children)
    {
        root->lchild = generate_rand_binary_tree(depth-1, cnt, reach_bottom);
        root->rchild = generate_rand_binary_tree(depth-1, cnt, reach_bottom);
    }
    if(depth == 0)
        reach_bottom = true;
    return root;
}


template <typename TreeNode>
TreePathNode* longest_path(TreeNode * root, int depth)
{
    if (root == NULL)
        return NULL;
    TreePathNode *d, *dl, *dr;
    // printf("node,depth:%d, %d\n", root->data, depth);
    d  = new TreePathNode(0,0,0,0);
    dl = longest_path(root->lchild,depth+1);
    dr = longest_path(root->rchild,depth+1);
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
                free_tree(&(d->lchild->rchild));
                assert(NULL == d->lchild->rchild);
            }
            else if (dl && d->lchild->depth_left < d->lchild->depth_right)
            {
                free_tree(&(d->lchild->lchild));
                assert(NULL == d->lchild->lchild);
            }
            // delete the grandchidren from his rchild.
            if (dr && d->rchild->depth_left > d->rchild->depth_right)
            {
                free_tree(&(d->rchild->rchild));
                assert(NULL == d->rchild->rchild);
            }
            else if (dr && d->rchild->depth_left < d->rchild->depth_right)
            {
                free_tree(&(d->rchild->lchild));
                assert(NULL == d->rchild->lchild);
            }
            break;
        // the max path is from lchild, so free delete rchild.
        case 2:
            free_tree(&(d->rchild));
            break;
        // the max path is from rchild, so free delete lchild.
        case 4:
            free_tree(&(d->lchild));
        // default:
        //     printf("ERROR! unknown come_from code: %d\n", d->come_from);
    }
    return d;
}


void  print_node(TreeNode *node)
{
    cout << node->data << endl;
}


void  test()
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
    // free_tree(root);
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}