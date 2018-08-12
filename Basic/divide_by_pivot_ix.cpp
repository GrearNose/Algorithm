#include <ctime>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

/*
divide an indexable list (array, vector, etc) into two sublists
La and Lb such that all elements in La is not greater than L[pv_ix]
and all elements in Lb is not less than L[pv_ix].
list  an indexable list (array or vector);
len   length of the list;
pv_ix index of the pivot element.
return the index of the pivot element in the divided list.
*/
template <typename T>
int divide_by_pivot_ix(T*list, int len, int pv_ix)
{
    if (len < 1 || pv_ix < 0 || pv_ix >= len)
    {
        return -1; // invalid arg.
    }
    T pivot = list[pv_ix]; // extract the pivot element.
    // move list[0] to list[pv_ix] and treat list[0] as an empty space.
    list[pv_ix] = list[0];
    int i = 0, j = len - 1;
    while(i < j)
    {
        // find an elem less than pivot in the right part.
        while(i < j && list[j] >= pivot)
            -- j;
        // move that elem to the empty space list[i], and the list[j] is empty.
        list[i] = list[j];
        // find and elem greater than the pivot in the left part.
        while(i < j && list[i] <= pivot)
            ++ i;
        // move that elem to the empty space list[j],
        // and then list[i] is empty again.
        list[j] = list[i];
    }
    // now it must be true that i == j, where the unit of list is empty.
    // assert(i == j);
    list[i] = pivot;

    return i;
}

void test()
{
    int n = 23;
    int *arr = new int[n];
    int min  = 0, mx = 33;
    srand(time(NULL));
    cout << "the original array: ";
    for (int i = 0; i < n; ++i)
    {
        arr[i] = min + rand() % mx;
        cout << arr[i] << " ";
    }
    cout << endl;

    int pv_ix0, pv_ix1;
    pv_ix0 = rand() % n;
    printf("divided array with pivot = %d \n", arr[pv_ix0]);
    
    pv_ix1 = divide_by_pivot_ix(arr, n, pv_ix0);

    printf("pivot index of the divided array: %d\n", pv_ix1);
    cout << "the divided array:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}