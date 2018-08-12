#include <algorithm>
#include <ctime>
#include <cassert>
#include <vector>
#include <iostream>
#define N 52
using namespace  std;

/*
Given a sorted array, determind whether there exists some nums
that will add up to a given sum. The complexity is o(2^n),
still not have a high possiblity to find the combinition.
*/
template <typename T>
bool has_a_sum(T*arr, unsigned len, int sum_cur,\
    int sum_target, vector<int> &nums, int depth=0)
{
    if( len < 1 || sum_cur > sum_target)
        return false;

    if (sum_cur == sum_target)
    {
        cout << "depth = " << depth << ": ";
        for (unsigned i = 0; i < nums.size(); ++i)
            cout << nums[i] << " ";
        cout << endl;
        return true;
    }

    if(sum_cur+arr[0] > sum_target) // impossible to find feasible num in the rest part.
        return false;
    // choose arr[0]
    nums.push_back(arr[0]);
    if(has_a_sum(arr+1, len-1, sum_cur+arr[0], sum_target, nums, depth+1))
        return true;
    // not choose arr[0]
    nums.pop_back();
    return has_a_sum(arr+1, len-1, sum_cur, sum_target, nums, depth+1);
}

/*
Determind whether there exits several nums in the array that add up to a sum
by first sorting and then prune the enumerating of all possible combinitons,
complexity o(2^n), when n is large (e.g. n > 48), it's infeasible to do so.
*/
template <typename T>
bool has_a_sum_prune(T*arr, unsigned len, int sum)
{
    sort(arr,arr+len);
    vector<int> nums;
    return has_a_sum(arr, len, 0, sum, nums);
}

void test()
{
    int arr[N], min = -3, mx = 23, sum = 0;
    srand(time(NULL));
    cout << "the array: ";
    for (int i = 0; i < N; ++i)
    {
        arr[i] = min + rand() % mx;
        cout << arr[i] << " ";
    }

    cout << endl << "sum: ";
    for (int i = 0; i < N; ++i)
    {
        if(rand() % 2)
        {
            sum += arr[i];
            cout << arr[i] << " ";
        }
    }
    cout << " = " << sum << endl;
    if (has_a_sum_prune(arr, N, sum))
        cout << "correct !" << endl;
    else
        cout << "Wrong!" << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}