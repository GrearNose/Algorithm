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
return: index of the entrance point of the loop
      if found, NULL otherwise.
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
        pFast = pFast->next->next;
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
        pFast = pFast->next;
        if (pSlow == pFast)
        {
            return pSlow;
        }
        // ++ cnt;
    }
    return NULL;
}

/*
Judge to given linked lists overlap with each other by concatenate them
into a new list, and judge whether there is a loop. O(L1+L2)
list1: the linked list one;
list2: the linked list two;
return: the pointer to the first overlapping node if
       they overlap with each other, NULL otherwise.
*/
NodeType* overlapped_linked_list_concat(NodeType *list1, NodeType *list2)
{
    NodeType *p, *q;
    if ( list1 == NULL || list2 == NULL)
        return NULL;
    for(p = list1; p->next != NULL; p = p-> next);
    p->next = list2;
    q = existsLoop(list1);
    p->next = NULL; // split into the original two linked lists.
    return q;
}

/*
Generate a linked list without head node and return
the pointer to its first node. The NodeType has two
fields next and data, where data is of type int.
Each node's data is assigned a int ascendingly in
the range [begin, end].
Arg:
begin: value of the first node's data;
end: value of the last node's data;
Return: pointer to the first node of the list if
begin < end, NULL otherwise.
*/
NodeType* gen_list_in_range(int begin, int end)
{
    if (begin > end)
        return NULL;
    NodeType *head = NULL, *p, *q;
    for (int value = begin; value <= end; ++value)
    {
        p = new NodeType();
        p->data = value;
        p->next = NULL;
        
        if (head != NULL)
        {
            q->next = p;
            q = p;
        }
        else
            head = q = p;
    }
    return head;
}

void test()
{
    int i, N = 6;
    NodeType *list1, *list2, *p, *q, *p_overlap;
    list1 = gen_list_in_range(0,N);
    list2 = gen_list_in_range(N+1,N+N/2);

    cout << "list1: ";
    for (p = list1; p != NULL; p = p->next)
        cout << p->data << ",";
    cout << "\nlist2:";
    for (p = list2; p != NULL; p = p->next)
        cout << p->data << ",";
    cout << endl;

    for (p = list1, i = 0; i < N/3; ++i)
        p = p->next;
    for (q = list2; q->next != NULL; q = q->next)
        q = q->next;

    cout << "Set overlap from node in list1: "\
         << i << ", data:" << p->data << endl;
    q->next = p; // make a loop with p as the entrance point.

    p_overlap = overlapped_linked_list_concat(list1,list2);

    cout << "overlapped_linked_list_concat: ";
    if (p_overlap == p)
        cout << "correct!" << endl;
    else
    {
        cout << "Wrong, ";
        if (p_overlap == NULL)
        {
            cout << "NULL " << endl;
        }
        else
        {
            cout << "correct point: "<< p << " vs. wrong: "\
             << p_overlap << " data:" << p_overlap->data << endl;
        }
    }
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}