#include <vector>
#include <map>
#include <ctime>
#include <iostream>

using namespace std;

template <typename T>
void print_arr(const T *arr, int len, const string &msg);

/*
get the LIS(longest Increasing Subsequence) of an given array,
using a DP algorithm with complexity of o(nlogn).
Args:
arr: the array to find the LIS;
seq_LIS: a vector the get the LIS found by this func, if needed.
*/
template <typename T>
int LIS(T*arr, int len)
{
    if (NULL == arr || len < 1)
        return -1;
    int mxlen = 0;
    T x, B[len] = { arr[0] };
 
    for (int i = 0; i < len; ++i)
    {
        x = arr[i];
        if (mxlen == 0 || x > B[mxlen-1]) // append
        {
            B[mxlen] = x;
            ++ mxlen;
        }
        else // find the least upper bound.
        {
            int l = 0, h = mxlen-1;
            while(l <= h) // compare until l>h, in case that x>B[l] and l==h.
            {
                int m = (l+h) >> 1; // (l+h)/2
                if(x < B[m])
                    h = m - 1;
                else if(x > B[m])
                    l = m + 1;
                else
                {
                    l = m;
                    break;
                }
            }
            if(x < B[l]) // not update when x == B[l]
                B[l] = x;
        }
    }

    return mxlen;
}

void test()
{
    const int len = 10;
    // lower bound of the random num, modify it to change
    // the lower bound, such as negative num.
    int min = 0;
    // upper bound of the random num: min + mx
    int mx = 2*len;
    int *arr = NULL;
    arr = new int[len];
    if ( NULL == arr)
    {
        cout << "No memory to new an array!" << endl;
        return;
    }
    srand(time(NULL));
    for (int i = 0; i < len; ++i)
        arr[i] = rand() % mx + min;
    print_arr(arr, len, "The array: ");

    int len_LIS = LIS(arr, len);
    cout << "len of LIS: " << len_LIS << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}

template <typename T>
void print_arr(const T *arr, int len, const string &msg)
{
    if (NULL == arr)
    {
        cout << msg << "NULL!" << endl;
        return ;
    }
    cout << msg;
    for (int i = 0; i < len; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}