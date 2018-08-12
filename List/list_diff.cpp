#include <cstdlib>
#include <iostream>
#include <set>
using namespace std;

typedef int DataType;

typedef struct NodeType
{
    DataType data;
    NodeType *next;
} NodeType;

/*
Different set of two single linked list A and B.
*/
void diff_list(NodeType *list1, NodeType *list2)
{
    NodeType *p, *q;
    std::set<DataType>set;
    if (list1 == NULL || list2 == NULL)
    {
        p = list1;
        while(p != NULL) // when list1 is not NULL, list2 is NULL.
        {
            cout << p->data << ",";
            p = p->next;
        }
        cout << endl;
        return;
    }

    // find out the shorter one and assign it to p.
    p = list2;
    while(p != NULL)
    {
        set.insert(p->data);
        p = p->next;
    }
    q = list1;
    while(q != NULL)
    {
        if (set.find(q->data) == set.end())
        {
            cout << q->data << ",";
        }
        q = q->next;
    }
    cout << endl;
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

    cout << "list1: ";
    for(p=list1; p != NULL; p = p->next)
        cout << p->data << "," ;

    cout << "\nlist2: ";
    for(p=list2; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << endl;

    cout << "diff: ";
    diff_list(list1,list2);
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}