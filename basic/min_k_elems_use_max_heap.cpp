#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#define N 1000000

using namespace std;

/*
Print elements of an array in a line.
msg  the message describing the array to print;
list head address of the array;
n    length of the array.
reverse: print the array reversly.
*/
void print_list(string msg, int *list, int n, bool reverse=false)
{
    cout << msg << endl;
    if (! reverse)
    {
        for (int i = 0; i < n; ++i)
            cout << list[i] << " ";
        cout << endl;
    }
    else
    {
        for (int i = n-1; i >= 0; --i)
            cout << list[i] << " ";
        cout << endl;   
    }
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
Find out the first k minimum elements in a array and put them in the head of
the array by using a max heap.
A heap which is a binary tree whose non-leaf nodes are always larger (max heap)
or smaller (min heap) than their left and/or right childrens. Build a max heap
of k element from the first k elements in the array, and for each element from
the rest part of the array, replace that element with the top of the heap if
the element is smaller than the top. complexity = O(nlog(k)).
=== args ===
arr   head address of the array;
n     length of the array;
k     the number of minimum elements to output;
sorted whether to sort the result ascendingly.
*/
void minKElem(int * arr, int n, int k, bool sorted=false)
{

    if (k < 1 || n < 1 || n < k) // invalid input.
    {
        return;
    }
    /* Build a maxheap of the first k elements in the array.*/
    for (int i = k/2-1; i >= 0; --i) // start from the last non-leaf node.
    {
        adjust_heap(arr,i,k);
    }
    // insert each  elem from the rest part if it's smaller than the top
    // of the heap.
    for (int i = k; i < n; ++i)
    {
        if (arr[i] < arr[0])
        {
            int tmp   = arr[0];
            arr[0]   = arr[i];
            arr[i] = tmp;
        }
        adjust_heap(arr,0,k);
    }
    if (sorted)
    {
        sort(arr, arr + k);
    }
}

void test()
{
    int i, k = 0;
    int arr1[N], arr2[N], min = 0, mx = 333;
    clock_t t0, t1, t2, t3;
    srand(time(NULL));
    while(k == 0)
    {
        k = rand() % N;
    }
    // k = 10;

    printf("k,N: %d,%d\n", k,N);
    cout << "Randomly initializing the array..." << endl;
    t0 = clock();
    for (i = 0; i < N; ++i)
    {
        arr1[i] = arr2[i] = min + rand() % mx;
    }

    cout << "Finding minimum k elems ... " << endl;
    t1 = clock();
    minKElem(arr1, N, k, true);
    t2 = clock();

    cout << "Soring the array for comparing ..." << endl;
    sort(arr2,arr2+N);
    t3 = clock();

    cout << "Comparinng the result from sort: ";
    for (i = 0; i < k; ++i)
    {
        if (arr1[i] != arr2[i])
        {
            printf("inconsistent at ix:%d, arr1:%d, arr2: %d\n", i, arr1[i], arr2[i]);
            break;
        }
    }
    if (i == k)
    {
        cout << "Correct!" << endl;
    }

    // // void print_list(string msg, int *list, int n)
    // print_list("arr1: ", arr1, k);
    // print_list("arr2: ", arr2, k);

    cout << "\nTime consumption: " << endl;
    printf("initialization: %f Sec\n", (float)(t1-t0)/CLOCKS_PER_SEC);
    printf("minKElem: %f Sec\n", (float)(t2-t1)/CLOCKS_PER_SEC);
    printf("sort: %f Sec\n", (float)(t3-t2)/CLOCKS_PER_SEC);
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}