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
Sort a linked list whose nodes have type of NodeType
which has two field, 'data' of DataType and 'next',
ascendingly(default) or descendingly.
Args
NodeType: type of the nodes in the list, must have two
    field 'data' and 'next';
DataType: type of the 'data' field in NodeType;
head: a pointer to the first node of the linked;
cmp: the func to implementing '<' (for ascending sort)
     or '>' (for descending sort).
*/
template<typename NodeType, typename DataType>
void list_sort(NodeType *head, bool (*cmp)(NodeType*,NodeType*)=NULL)
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
            if ((cmp!=NULL && cmp(q,p_min)) \
                || (cmp==NULL && q->data < p_min->data))
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
Generate a linked list without head node and return
the pointer to its first node. The NodeType has two
fields next and data, where data is of type int.
Each node's data is assigned a rand int in range [1,MAX].
Arg:
len: length of the linked list to generate;
MAX: upper bound of node's data field in random generating.
Return: pointer to the first node of the list.
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

/*
In inline func to implement the operator '>'
for NodeType* variables.
*/
inline bool lg(NodeType*p,NodeType*q)
{
    if (p == NULL || q == NULL)
    {
        return false; // invalid arg, cannot compare.
    }
    return p->data > q->data;
}


void test()
{
    int MAX = 17;
    NodeType *list1, *list2, *p;

    srand(time(NULL));
    list1 = gen_rand_list(1+rand()%MAX, MAX);
    list2 = gen_rand_list(1+rand()%MAX, MAX);

    cout << "Original list1: ";
    for(p=list1; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << "\nsorting ..." << endl;

    list_sort<NodeType,DataType>(list1);
    cout << "Ascending list1: ";
    for(p=list1; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << endl;


    cout << "\nOriginal list2: ";
    for(p=list2; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << "\nsorting ..." << endl;

    list_sort<NodeType,DataType>(list2,lg);
    cout << "Descending list2: ";
    for(p=list2; p != NULL; p = p->next)
        cout << p->data << "," ;
    cout << endl;    
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}