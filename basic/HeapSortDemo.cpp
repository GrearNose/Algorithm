#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
// #define N 100000000
#define N 10000000
// #define N 35
using namespace std;

/*
Print elements of an array in a line.
msg  the message describing the array to print;
list head address of the array;
n    length of the array.
*/
void print_list(string msg, int *list, int n)
{
    cout << msg << endl;
    for (int i = 0; i < n; ++i)
        cout << list[i] << " ";
    cout << endl;
}

// TODO still need to perfect the output format.
void print_heap(string msg, int * heap, int n)
{
    int mx = 0, width = 0, h = 0;
    for (int i = 0; i < n; ++i)
        mx = (abs(heap[i]) > mx)? abs(heap[i]) : mx;
    width = log10(mx) + 1;
    // heigh = ceil((log(n)/log(2)));
    cout << msg << endl;
    for (int i = 0; i < n; ++i)
    {
        if (i + 1 == pow(2,h))
        {
            if (i > 0)
                cout << endl;
            ++ h;
            for (int j = 0; j < width-i; ++j)
                for (int k = 0; k < width + 1; ++k)
                    cout << " ";
        }
        // cout << heap[i] << " ";
        int lout = printf("%d", heap[i]);
        for (int j = 0; j < width-lout+1; ++j)
            cout << " ";
    }
    cout << endl;
}

/*
Convert a heap root at ix into a max heap by recursively swapping
the root (top of the heap) and the max of its two direct children
if root is not the max. N.B. before performing this adjusting,
both the left and right children should be max heaps, thus do the
conversion to the heap from bottom to top when calling this func.
*/
void adjust_heap(int * heap, const int ix, int n)
{
    if (ix*2 > n)
        return;

    int tmp, ix_mx = ix, ix1 = 2*ix, ix2 = 2*ix+1;
    if (ix1 < n && heap[ix1] > heap[ix_mx])
        ix_mx = ix1;
    if (ix2 < n && heap[ix2] > heap[ix_mx])
        ix_mx = ix2;
    if (ix_mx != ix)
    {
        tmp         = heap[ix];         
        heap[ix]    = heap[ix_mx];
        heap[ix_mx] = tmp;
        adjust_heap(heap, ix_mx, n);
    }
}


/*
Sort an array ascendingly using heap sort.
A heap which is a binary tree whose non-leaf nodes are always larger (max heap)
or smaller (min heap) than their left and/or right childrens. Sort the array
by firstly converting it into a max heap and then repeatly reduce the heap by
moving(swapping) the top node(max one in the heap) to the last node at the
bottom of the heap, exclude it from the heap and adjust the heap into a max
heap.
=== args ===
heap  head address of the array;
n     length of the array.
*/
void heap_sort(int * heap, int n)
{
    /* Build a maxheap by repeatly building small maxheaps and
    merging them into large ones pair by pair, from heap from
    heap rooted at low position to ones at high position in
    heap (heap). N.B low position of the heap corresponds to
    high index of the array, and top of the heap corresponds
    to index 0.*/
    for (int i = n/2-1; i >= 0; --i) // start from the last non-leaf node.
    {
        adjust_heap(heap,i,n);
    }
    // repeatly reduce the max heap into a small one by removing
    // the top node and replace its pos with the last node.
    for (int i = 1; i < n; ++i)
    {
        int tmp   = heap[0];
        heap[0]   = heap[n-i];
        heap[n-i] = tmp;

        adjust_heap(heap,0,n-i);
    }
}

int main(int argc, char const *argv[])
{
    int i, lower = 0, upper = 3333;
    int * heap  = new int[N];
    int * heap2 = new int[N];
    clock_t t0, t1, t2, t3, t4;

    srand(time(0));
    t0 = clock();

    cout << "heap sorting demo\nInitializing the arrays...\n";
    for (int i = 0; i < N; ++i)
        heap[i] = heap2[i] =  lower + rand() % (upper-lower);
    // print_heap("unsorted heap: ", heap, N);
    t1 = clock();
    heap_sort(heap, N);
    t2 = clock();
    sort(heap2,heap2+N);
    t3 = clock();

    // print_heap("sorted heap: ", heap, N);
    // print_list("sorted by heap_sort:", heap, N);
    // print_list("sorted by sort:", heap2, N);

    cout << "Done. Comparing to the result by sort from STL: ";

    for (i = 0; i < N; ++i) // inconsistent when N = 1000
    {
        if (heap[i] != heap2[i])
        {
            cout << endl << "inconsistent result at ix: " << i << endl;
            break;
        }
    }
    if (i == N)
        cout << "Correct !" << endl;
    t4 = clock();

    cout << "time_init:      " << (float)(t1-t0) / CLOCKS_PER_SEC << endl;
    cout << "time_heap_sort: " << (float)(t2-t1) / CLOCKS_PER_SEC << endl;
    cout << "time_qsort:     " << (float)(t3-t2) / CLOCKS_PER_SEC << endl;
    cout << "time_checking:  " << (float)(t4-t3) / CLOCKS_PER_SEC << endl;

    return 0;
}