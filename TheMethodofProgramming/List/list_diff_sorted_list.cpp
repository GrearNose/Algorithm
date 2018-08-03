#include <cstdlib>
#include <iostream>
using namespace std;

typedef int DataType;

typedef struct NodeType
{
    DataType data;
    NodeType *next;
} NodeType;

/*
Output the different set of two sorted(ascendingly)
single linked list.
*/
void diff_sorted_list(NodeType *list1, NodeType *list2)
{
    if (list1 == NULL || list2 == NULL)
        return;
    NodeType *p, *q;
    p = list1;
    q = list2;
    while(p != NULL && q != NULL)
    {
        if (p->data == q->data)
        {
            DataType d = p->data;
            while(p != NULL && p->data == d)
                p = p->next;

            d = q->data;
            while(q != NULL && q->data == d)
                q = q->next;
        }
        // then this p->data is not in list2.
        else if(p->data < q->data)
        {
            cout << p->data << ",";
            p = p->next;
        }
        else
            q = q->next;
    }

    while(p != NULL) // the rest part.
    {
        cout << p->data << ",";
        p = p->next;
    }
    cout << endl;
}

/*
A simple func to sort a linked list.
*/
void list_sort(NodeType *head)
{
    if (head == NULL)
        return;
    NodeType *p_cur, *p_min, *q;
    DataType d;
    // cout << "\nlist sorting: \n";
    for(p_cur = head; p_cur->next != NULL; p_cur = p_cur->next)
    {
        for(q = p_min = p_cur; q != NULL; q = q->next)
        {
            if (q->data < p_min->data)
                p_min = q;
        }
        if (p_min != p_cur)
        {
            // cout << p_min->data << ", " ;
            d = p_cur->data;
            p_cur->data = p_min->data;
            p_min->data = d;
        }
    }
    // cout << endl;
}

/*
Auxiliary func to generate a linked list
with random data field.
*/
NodeType* gen_rand_list(int len,int MAX=13)
{
    if (len < 1)
        return NULL;
    NodeType *head = NULL, *p, *q;
    for (int i = 0; i < len; ++i)
    {
        p = new NodeType();
        // p->data = i;
        p->data = rand() % MAX;
        p->next = NULL;
        
        if (head != NULL)
        {
            q->next = p;
            q = p;
        }
        else
            head = q = p;
        // cout << p->data << ",";
    }
    return head;
}

void test()
{
    int N   = 10;
    NodeType *list1, *list2, *p, *q, *p1, *p2;
    list1   = list2 = NULL;
    int MAX = 17;

    srand(time(NULL));
    // list1 = gen_rand_list(N, MAX);
    // list2 = gen_rand_list(N/2, MAX);
    list1 = gen_rand_list(1+rand()%MAX, MAX);
    list2 = gen_rand_list(1+rand()%MAX, MAX);

    // cout << "list1: ";
    // for(p=list1; p != NULL; p = p->next)
    //     cout << p->data << "," ;

    // cout << "\nlist2: ";
    // for(p=list2; p != NULL; p = p->next)
    //     cout << p->data << "," ;
    // cout << endl;

    list_sort(list1);
    list_sort(list2);

    cout << "list1: ";
    for(p=list1; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << "\nlist2: ";
    for(p=list2; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << endl;

    cout << "diff: ";
    diff_sorted_list(list1,list2);
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}