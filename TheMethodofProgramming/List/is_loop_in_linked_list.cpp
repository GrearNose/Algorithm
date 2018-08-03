#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

typedef int DataType;

typedef struct NodeType
{
    DataType data;
    NodeType *next;
} NodeType;

/*
Judge whether a linked list has loop.
head: head of the linked list;
return: index of the entrance point if found,
    NULL otherwise.
*/
NodeType* existsLoop(NodeType*head)
{
    NodeType *pSlow, *pFast;
    pSlow = pFast = head;
    int cnt = 0;
    while(pSlow != NULL && pFast->next != NULL)
    {
        // cout << "(" << pSlow->data << "," << pFast->data <<")" << " ";
        pSlow = pSlow->next;
        pFast = pFast->next->next; // move fast
        if (pSlow == pFast)
        {
            // cout << "First meet at pos: " << cnt << endl;
            break;
        }
        ++ cnt;
    }
    pSlow = head;
    while(pSlow != NULL && pFast->next != NULL)
    {
        // cout << "(" << pSlow->data << "," << pFast->data <<")" << " ";
        pSlow = pSlow->next;
        pFast = pFast->next; // move at same speed.
        if (pSlow == pFast)
        {
            return pSlow;
        }
    }
    return NULL;
}

void test()
{
    int i, N = 10;
    NodeType *head, *p, *q;
    head = q = new NodeType();
    for (i = 0; i < N; ++i)
    {
        p = new NodeType();
        p->data = i;
        p->next = NULL;
        q->next = p;
        q = p;
    }
    for (p = head, i = 0; i < N/2; ++i)
    {
        p = p->next;
    }
    cout << "Set entrance point: " << i << endl;
    q->next = p; // make a loop with p as the entrance point.
    p = existsLoop(head);
    if (p)
    {
        cout << "correct!\nFound the entrance point with data: "\
         << p->data << endl;
    }
    else
        cout << "Wrong !" << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}