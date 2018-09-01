#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;


/*
Find the greatest element smaller than a given value in a
non-descendingly sorted array using binary search, and return its index.
Args
arr: a ascendingly sorted array or vector;
len: number of elements in arr;
val: the element to search in arr;
return: index of the greatest elem < val if found, -1 otherwise.
*/
template<typename T1, typename T2>
int lower_bound_strict(const T1 arr, int len, const T2 val)
{
    if (NULL==arr || len <= 0 || val <= arr[0])
        return -1;
    if (arr[len-1] < val)
        return len-1;
    if (1 == len)
        return (arr[0] < val) ? 0 : -1;

    int l = 0, h = len-1, m = 0;
    // now len >= 2, l < h, arr[0] < x <= arr[-1].
    while(l < h)
    {
        m = (l + h) >> 1;
        if (arr[m] < val) // ensure arr[l] < val always true.
        {
            if (l == m) // then l+1 == h, such that m = (l+h)/2 == l
            {           // arr[m]=arr[l] < val <= arr[h], then arr[m] is the target.
                h = m;
                break;
            }
            l = m;
        }
        else // val <= arr[m]
        {
            // there might be more than elem == val,
            // and in such case, we need to lower h to find
            // the greatest h, such that arr[h] < val.
            h = m - 1;
            if(arr[h] < val) // found the target
                break;
        }
    }
    // now l == h, and note that arr[l] < val is always true,
    // and arr[h] is the greatest elem < val.
    return h;
}


/*
Find the greatest lower bound (i.e. the greatest elem <= val) of a given value
in a non-descendingly, sorted array using binary search, and return its index.
Args
arr: a ascendingly sorted array or vector;
len: number of elements in arr;
val: the element to search in arr;
return: the index of the greatest elem <= val, if more than one are found,
        return the index of the FIRST one, -1 otherwise.
*/
template<typename T1, typename T2>
int lower_bound(const T1 arr, int len, const T2 val)
{
    if (NULL==arr || len <= 0 || val < arr[0])
        return -1;
    // not use '=' here in order to find the index of the first satifying elem.
    if (arr[len-1] <= val)
        return len-1;
    if (1 == len)
        return (arr[0] <= val) ? 0 : -1;

    int l = 0, h = len-1, m = 0;
    // now len >= 2, l < h, arr[0] < x <= arr[-1].
    while(l < h)
    {
        m = (l + h) >> 1;

        if (arr[m] < val) // ensure arr[l] < val always true.
        {
            if (l == m) // then l+1 == h, (l+h)/2 == l, dead loop if not deal with it.
            {           // h = m is the greatest h value
                        // that breaks the condition "val <= arr[h]".
                h = m;
                break;
            }
            l = m;
        }
        else // val <= arr[m]
        {
            // there might be more than elem == val,
            // and in such case, we need to lower h to find
            // the greatest h value that breaks the upper bound
            // condition: arr[h] <= val.
            h = m - 1;
            if(arr[h] < val) // found the target
                break;
        }
    }
    // now l == h, and note that arr[l] < val is always true,
    // and h = l is the greatest value that breaking the condition:
    // arr[h] >= val.
    // thus now, arr[h] < val <= arr[h+1], and arr[h+1] is the
    // (first if more than one) greatest lower bound.
    if (arr[h+1] == val)
        return h + 1;// arr[h+1] is the first one of the greatest lower bound.
    else             // N.B. in this case, arr[l] == arr[h] < x < arr[h+1]
        return h;    // arr[h] is the greatest lower bound.
}


/*
Find the least upper bound of an given value 
in a non-descendingly sorted array using binary search.
Args
arr: a ascendingly sorted array or vector;
len: number of elements in arr;
val: the element to search in arr;
return: the index of the the least elem >= val, if more that one are found,
     return the index of the LAST one.
*/
template<typename T1, typename T2>
int upper_bound(const T1 arr, int len, const T2 val)
{
    if (NULL==arr || len <= 0 || val > arr[len-1])
        return -1;
    // cannot use val <= arr[len-1] here, as there might be smaller upper bound.
    if (val == arr[len-1])
        return len-1;
    if (val <= arr[0] || 1 == len)
        return (val <= arr[0]) ? 0 : -1;

    int l = 0, h = len-1, m;
    // now len >= 2, l < h, arr[0] < x <= arr[-1].
    while(l < h)
    {
        m = (l + h) >> 1;

        if (val < arr[m]) // ensure val < arr[h] always true.
        {
            h = m;
            if (arr[m-1] < val)
                return h;
        }
        else // arr[m] <= val
        {
            // need to increase l to find the least l
            // that breaks the contidion of lower bound:
            // arr[l] <= val.
            l = m + 1;
        }
    }
    // now l == h, arr[l-1] <= x < arr[l], arr[l-1] is
    // the last one satisfying the lower bound condition if l-1 is valid.
    if (arr[l-1] == val) // arr[l-1] is the last one in the least upper bound.
        return l-1;
    else           // N.B. arr[l-1] < x < arr[l], 
        return l;  // arr[l] is the least upper bound.
}


/*
Find the strict upper bound of a value in a non-descendingly sorted array
(i.e. the first elem > x) using binary search.
Args
arr: a ascendingly sorted array or vector;
len: number of elements in arr;
val: the element to search in arr;
return: the index of the index of the first elem > val if found, -1 otherwise.
*/
template<typename T1, typename T2>
int upper_bound_strict(const T1 arr, int len, const T2 val)
{
    if (NULL==arr || len <= 0 || val >= arr[len-1])
        return -1;
    if (val < arr[0] || 1 == len)
        return (val < arr[0]) ? 0 : -1;

    int l = 0, h = len-1, m;
    // now len >= 2, l < h, arr[0] < x <= arr[-1].
    while(l < h)
    {
        m = (l + h) >> 1;

        if (val < arr[m]) // ensure val < arr[h] always true.
            h = m;
        else // arr[m] <= val
            // need to increase l to find the least l
            // that breaks the contidion of lower bound:
            // arr[l] <= val.
            l = m + 1;
    }
    // now l == h, arr[l-1] <= x < arr[l], arr[l] is
    // the first one breaking the lower bound condition.
    return l;
}

template<typename T>
bool test_caller(T*arr, int len, T val, int (*func)(T*,int, T), const string &msg)
{
    if (NULL == arr || len <= 0 || func == NULL)
        return false;

    cout << msg;
    int ix = (*func)(arr,len, val);
    if (ix > -1)
    {
        cout << "arr[" << ix << "] = " << arr[ix] << endl;
        return true;
    }
    else
    {
        cout << "Not found!" << endl;
        return false;
    }
}

void test()
{
    int *arr;
    // int len = 1;
    int len = 2;
    // int len = 3;
    // int len = 4;
    int min = 3, mx = 23;
    arr = new int[len];
    srand(time(NULL));
    for (int i = 0; i < len; ++i)
        arr[i] = min +  rand() % mx;
    sort(arr,arr+len);
    cout << "arr: ";
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << endl;
    // use different cases for testing.
    // int ix = rand() % len;
    // int val = arr[ix] + 1;
    // int val = arr[0];
    // int val = arr[1];
    // int val = arr[len-1];
    // int val = arr[len-2];
    int val =  min +  rand() % mx;
    cout << "Value to search: " << val << endl;

    bool flg1, flg2, flg3=false, flg4=false;
    flg1 = test_caller(arr,len,val,lower_bound_strict, "strict lower bound: ");
    flg2 = test_caller(arr,len,val,lower_bound, "lower bound: ");
    flg3 = test_caller(arr,len,val,upper_bound, "upper bound: ");
    flg4 = test_caller(arr,len,val,upper_bound_strict, "strict upper bound: ");

    if (flg1 && flg2 && flg3 && flg4)
        cout << "all found !" << endl;
    else
        cout << "not found all !" << endl;
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}