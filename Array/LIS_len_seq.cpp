#include <vector>
#include <map>
#include <ctime>
#include <iostream>
#define DEBUG 1 // open this macro to see info during the procedure.
// #define DEBUG 0
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
int LIS(T*arr, int len, vector<T>* const seq_LIS=NULL)
{
    if (NULL == arr || len < 1)
        return -1;
    int mxlen = 0;
    T x, B[len] = { arr[0] };
    vector<vector<T>*> *subLIS = NULL;

    if (NULL != seq_LIS)
        subLIS = new vector<vector<T>*>();
    
    for (int i = 0; i < len; ++i)
    {
        #if DEBUG
        cout << endl << "arr[" << i << "]: " << arr[i] << endl;
        cout << "B:     [ " ;
        for (int i = 0; i < mxlen; ++i)
            cout << B[i] << " ";
        cout << "]" << endl;
        #endif

        x = arr[i];
        if (mxlen == 0 || x > B[mxlen-1]) // append
        {
            B[mxlen] = x;
            #if DEBUG
            cout << "append x: " << x << endl;
            #endif
            if(NULL != seq_LIS)
            {
                vector<T> *seq = new vector<T>();
                if(mxlen > 0)
                {
                    vector<T> *seq_len_mxlen = (*subLIS)[mxlen-1];
                    for (int i = 0; i < mxlen; ++i)
                    {
                        T e = (*seq_len_mxlen)[i];
                        seq->push_back(e);
                    }
                }
                seq->push_back(x);
                subLIS->push_back(seq);
            }
            ++ mxlen;
        }
        else
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
                    l = m; // used to update ix.
                    break;
                }
            }
            if(x < B[l])
            {
                #if DEBUG
                cout << "Replace " << B[l] << " with " << x << endl;
                #endif
                int ix = l;
                B[ix] = x;
                if (NULL != seq_LIS)
                    (*((*subLIS)[ix]))[ix] = x;
            }
            #if DEBUG
            else
                cout << "Already appear in B." << endl;
            #endif
        }

        #if DEBUG
        if (NULL != seq_LIS)
            {
            cout << "subLIS: " << endl;
            for(vector<T>* seq : *subLIS)
            {
                for (T e : *seq)
                    cout << e << " ";
                cout << endl;
            }
        }
        #endif

    }
    if (NULL != seq_LIS)
    {
        #if DEBUG
        cout << "mxlen: " << mxlen << endl;
        #endif
        if (mxlen > 0)
        {
            // write the longest LIS.
            *seq_LIS = *(*subLIS)[mxlen-1];
            // free the memory of the elem held in subLIS.
            for (int i = mxlen; i > 0 ; --i)
            {
                delete((*subLIS)[i-1]);
                (*subLIS).pop_back();
            }
        }
    }

    return mxlen;
}

void test()
{
    vector<int> seq_LIS;
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

    // when only the length of LIS is required, not the LIS:
    // int len_LIS = LIS(arr, len);
    // cout << "len of LIS: " << len_LIS << endl;

    // when the LIS sequence is required, call it this way:
    LIS(arr, len, &seq_LIS);
    print_arr((int*)&seq_LIS[0], seq_LIS.size(), "LIS: ");
    
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