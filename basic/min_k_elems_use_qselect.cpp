#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#define N 10

using namespace std;

/*
Find out the minimum k elements in the array and put them in the head of the
array.
Use a pivot similar in qsort to divide the array into two subarray, Sa, Sb.
If k < |Sa|, then the k-th min element is in Sa;
if k = |Sa| + 1, then the k-th min element is the pivot;
if k > |Sa| + 1, then the k-th min element is the (k-|Sa|-1)-th element in Sb.
Complexity = O(n)
*/
void qselect(int*arr, int n, int k) 
{
    if (n < 1 || k < 0 || k >= n)
    {
        return; // invalid params or no need to cal when k == n.
    }

    int i, j, ix, pivot;
    ix      = rand() % n; // randomly choose a elem as the pivot.
    pivot   = arr[ix];    // extract the pivot
    arr[ix] = arr[0];     // move arr[0] to arr[ix], and treat arr[0] empty.
    i       = 0;
    j       = n-1;
    while(i < j)          // divide the array into two parts, Sa and Sb.
    {
        // find out the elem less than the pivot in the right part.
        while(i < j && arr[j] >= pivot) --j;
        // move arr[j] to the empty space at arr[i], and arr[j] will be empty.
        arr[i] = arr[j];
        // find out the elem greater than the pivot in the left part.
        while(i < j && arr[i] <= pivot) ++i;
        // move arr[i] to arr[j] and then arr[i] is empty again.
        arr[j] = arr[i];
    }
    arr[i] = pivot; // fill the empty space in the middle with the pivot.

    if (k < i)      // find k min elems from the left part, arr[:n].
    {
        qselect(arr, i, k);
    }
    else if(k > i + 1)// find k-(i+1) min elems from the right part arr[i+1:n].
    {
        qselect(arr+i+1, n-i-1, k-i-1);
    }
}

void test()
{
    int arr[N];
    int k = 3;
    int min  = 0, mx = 33;
    srand(time(NULL));
    cout << "the original array:\n";
    for (int i = 0; i < N; ++i)
    {
        arr[i] = min + rand() % mx;
        cout << arr[i] << " ";
    }
    cout << endl;

    qselect(arr, N, k);
    printf("The selected %d minimum elmement \n"\
        "are move to the head of the array:\n", k);
    for (int i = 0; i < N; ++i)
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