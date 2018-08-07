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
bool has_a_sum_enumerate(T*arr, unsigned len, int sum)
{
    if( len < 1)
        return false;
    // choose arr[0]
    if (sum-arr[0] == 0)
        return true;
    else if (has_a_sum_enumerate(arr+1, len-1, sum-arr[0]))
        return true;
    // not choose ar[0]
    if(has_a_sum_enumerate(arr+1, len-1, sum))
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
    if (has_a_sum_enumerate(arr,N,sum))//, nums))
        cout << "correct !" << endl;
    else
        cout << "Wrong!" << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}