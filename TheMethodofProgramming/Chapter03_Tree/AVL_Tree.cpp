#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

typedef int KeyType;
typedef int DataType;

typedef struct TreeNode
{
    KeyType key;
    DataType data;
    TreeNode *lchild, *rchild;
    // use DataType*d would be better,
    // but it requires to handle with NULL pointer exception,
    // which will make code complicated.
    TreeNode(KeyType k, DataType d)
    {
        key    = k;
        data   = d;
        lchild = rchild = NULL;
    }
} TreeNode;


template <class DataType, class KeyType>
class AVL_Tree
{
public:
    AVL_Tree(){};
    ~AVL_Tree();
    bool insert(const DataType &node);
    void preOrderTraverse(void(*visit)(DataType*));
    void inOrderTraverse(void(*visit)(DataType*));
    void postOrderTraverse(void(*visit)(DataType*));

private:
    TreeNode *root = NULL;

    void freeTree(TreeNode*);
};

template <class DataType, class KeyType>
void AVL_Tree<DataType,KeyType>::freeTree(TreeNode*root)
{
    cout << "destructing the AVL Tree ...\n";
    if (root = NULL)
    {
        return;
    }
    freeTree(root->lchild);
    freeTree(root->rchild);
    delete root;
}

template <class DataType, class KeyType>
AVL_Tree<DataType,KeyType>::~AVL_Tree()
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root);
}


template <class DataType, class KeyType>
bool AVL_Tree<DataType,KeyType>::insert(const DataType &node)
{

    if(root == NULL || node.key == root->key)
    {
        root = node;
    }
    else
    {
        TreeNode *q, *p = &root;
        while(p != NULL && node.key != p->key)
        {
            q = p;
            if (node.key < p->key)
                p = p->lchild;
            else
                p = p->rchild;
        }
        
        if (p == NULL)
        {
            if (node.key < q->key)
                q->lchild = &node;
            else
                q->rchild = &node;
        }
        else
        {
            p->data = node.data;
            return false;
        }
    }
    return true;
}


template<class DataType, class KeyType>
void AVL_Tree<DataType, KeyType>::preOrderTraverse(
                          void(*visit)(DataType*))
{
    if (NULL == root)
        return;
    visit(root);
    preOrderTraverse(root->lchild,visit);
    preOrderTraverse(root->rchild,visit);
}


template<class DataType, class KeyType>
void AVL_Tree<DataType, KeyType>::inOrderTraverse(
                        void(*visit)(DataType*))
{
    if (NULL == root)
        return;
    inOrderTraverse(root->lchild,visit);
    visit(root);
    inOrderTraverse(root->rchild,visit);
}

template<class DataType, class KeyType>
void AVL_Tree<DataType, KeyType>::postOrderTraverse(
                       void(*visit)(DataType*))
{
    if (NULL == root)
        return;
    postOrderTraverse(root->lchild,visit);
    postOrderTraverse(root->rchild,visit);
    visit(root);
}



void test()
{
    AVL_Tree<DataType,KeyType> t;

}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}