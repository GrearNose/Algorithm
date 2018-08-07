#include <algorithm>
#include <ctime>
#include <vector>
#include <iostream>
// #define N 15233
#define N 10000
using namespace std;

/*
Given a array of nums, determind whether there exit a way to choose
repeatably four of them so that they add up to a given sum.
The func has two loop and within the inner one, uses a 'clamp from two ends'
approach to find the other two nums in a complexity of o(n), thus the whole
comlexity is o(n^3). Its running time may be unacceptable when n > 1e5.
*/
template <typename T>
bool find_four_nums_add_up_to_a_sum(T*arr, unsigned len, int sum, vector<int> &nums)
{
    if ( NULL == arr || len < 1)
        return false;
    sort(arr, arr+len);
    for (unsigned i = 0; i < len; ++i)
    {
        for (unsigned j = 0; j < len; ++j)
        {
            int s = arr[i] + arr[j];
            if (s > sum)
                return false;
            int m = sum - s;
            for(unsigned k=0,l=len-1; k <= l; ) // allow k==l to select replicable nums.
            {
                s = arr[k] + arr[l];
                if (s == m)
                {
                    nums.push_back(arr[i]);
                    nums.push_back(arr[j]);
                    nums.push_back(arr[k]);
                    nums.push_back(arr[l]);
                    return true;
                }
                else if(s < m)
                    ++ k;
                else // s > m
                    -- l;
            }
        }
    }
    return false;
}

void test()
{
    int arr[N], min = -3, mx = 23, sum = 0;
    srand(time(NULL));
    cout << "len of arry: " << N;
    for (int i = 0; i < N; ++i)
    {
        arr[i] = min + rand() % mx;
        // cout << arr[i] << " ";
    }

    cout << endl << "sum: ";
    for (int i = 0; i < 4; ++i)
    {
        int ix = rand() % N;
        sum += arr[ix];
        cout << arr[ix] << " + ";
    }
    cout << " = " << sum << endl;
    vector<int> nums;
    if (find_four_nums_add_up_to_a_sum(arr,N,sum,nums))
    {
        cout << "solu: ";
        for (unsigned i = 0; i < nums.size(); ++i)
        {
            cout << nums[i] << " ";
        }
        cout << "\ncorrect !" << endl;
    }
    else
        cout << "Wrong!" << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}