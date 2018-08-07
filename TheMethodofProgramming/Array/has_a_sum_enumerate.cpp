#include <algorithm>
#include <ctime>
#include <cassert>
#include <vector>
#include <iostream>
#define N 48
using namespace  std;

/*
Determind whether there exits several nums in the array that add up to a sum
by enumerating all possible combinitons, complexity o(2^n),
when n is large (e.g. n > 48), it's infeasible to do so.
*/
template <typename T>
bool has_a_sum_enumerate(T*arr, unsigned len, int sum, vector<int> &nums, int depth=0)
{
    if( len < 1)
        return false;
    // choose arr[0]
    nums.push_back(arr[0]);
    sum -= arr[0];
    if (sum == 0)
    {
        cout << "depth = " << depth << ": ";
        for (unsigned i = 0; i < nums.size(); ++i)
            cout << nums[i] << " ";
        cout << endl;
        return true;
    }
    else if (has_a_sum(arr+1, len-1, sum, nums, depth+1))
        return true;
    // not choose arr[0]
    nums.pop_back();
    sum += arr[0];
    if(has_a_sum(arr+1, len-1, sum, nums, depth+1))
        return true;
    return false;
}

void test()
{
    int arr[N], mx = 7, sum = 0;
    std::vector<int> nums;
    srand(time(NULL));
    cout << "the array: ";
    for (int i = 0; i < N; ++i)
    {
        arr[i] = rand() % mx;
        cout << arr[i] << " ";
        if(rand() % 2)
            sum += arr[i];
    }

    cout << endl << "sum: " << sum << endl;
    if (has_a_sum(arr,N,sum, nums))
        cout << "correct !" << endl;
    else
        cout << "Wrong!" << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}