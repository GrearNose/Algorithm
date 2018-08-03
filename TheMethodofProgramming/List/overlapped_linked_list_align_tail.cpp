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
Judge to given linked lists overlap with each other by first
"align" them to the tail, and compare the tail of the longer
one with the shorter one from position L1-L2 where L1 is the
length of the longer one while L2 the shorter one. O(2*L1+L2).
list1: the linked list one;
list2: the linked list two;
return: the pointer to the first overlapping node if
       they overlap with each other, NULL otherwise.
*/
NodeType* overlapped_linked_list_align(NodeType *list1, NodeType *list2)
{
    int len1, len2, dif;
    NodeType *p, *q;
    if (list1 == NULL || list2 == NULL)
        return NULL;
    for(len1 = 0, p = list1; p->next != NULL; p = p->next, ++len1);
    for(len2 = 0, q = list2; q->next != NULL; q = q->next, ++len2);
    if (p != q)
        return NULL;
    if (len1 > len2)
    {
        p = list1;
        q = list2;
        dif = len1-len2;
    }
    else
    {
        p = list2;
        q = list1;
        dif = len2-len1;
    }

    for (int i = 0; i < dif; ++i) // align them to the tail.
        p = p->next;
    while(p != NULL && q != NULL)
    {
        if (p == q)
            return p;
        p = p->next;
        q = q->next;
    }
    cout << "Cannot find the entrance point, something wrong !" << endl;
    return NULL;
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

    p_overlap = overlapped_linked_list_align(list1,list2);

    cout << "overlapped_linked_list_align: ";
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
