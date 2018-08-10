#include <algorithm>
#include <ctime>
#include <cassert>
#include <vector>
#include <iostream>
#define N 25
using namespace  std;

/*
Find k nums that add up to a sum(>0) by enumerating all possible
combinitons, complexity o(2^n), when n is large (e.g. n > 23 ),
it's infeasible to do so.
*/
template <typename T>
void sum_of_k_nums(T*arr, unsigned len, int sum, vector<int> &nums, int depth=0)
{
    if( len < 1)
        return;
    static long cnt = 0;
    ++cnt;
    if (0 == cnt % 1000)
        printf("cnt: %ld\n", cnt);
    // choose arr[0]
    nums.push_back(arr[0]);
    sum -= arr[0];
    if (sum == 0)
    {
        cout << "depth = " << depth << ": ";
        for (unsigned i = 0; i < nums.size(); ++i)
            cout << nums[i] << " ";
        cout << endl;
    }
    else
        sum_of_k_nums(arr+1, len-1, sum, nums, depth+1);
    // not choose arr[0]
    nums.pop_back();
    sum += arr[0];
    sum_of_k_nums(arr+1, len-1, sum, nums, depth+1);
}

void test()
{
    int arr[N], mx = 7, sum;
    std::vector<int> nums;
    srand(time(NULL));
    cout << "the array: ";
    for (int i = 0; i < N; ++i)
    {
        arr[i] = rand() % mx;
        cout << arr[i] << " ";
    }

    for(sum = 0; !sum; sum = rand() % (3*mx));
    cout << "sum: " << sum << endl;

    sum_of_k_nums(arr,N,sum, nums);
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}