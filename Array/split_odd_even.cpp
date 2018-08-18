#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

/*
Split an array into two parts such that the first part (in front of the array)
contain all odd nums, and the second part(in rear of the array) contains all
even nums.
algorithm: use two indices, i and j, to traverse the array from its
         two ends towards its center, and swap arr[i], arr[j] when arr[i]
         is even and arr[j] is odd.

*/
template <typename T>
void split_odd_even(T arr[],int len)
{
    cout << endl << "len: " << len << endl;

    if (len < 2)
        return;
    int i, j;
    i = 0;
    j = len -1;
    while (i < j)
    {
        while(i < j && (1 == abs(arr[i] % 2)))
            ++ i;
        while (i < j && (0 == abs(arr[j] % 2)))
            -- j;
        swap(arr[i], arr[j]);
    }
}

void test()
{
    int *arr = NULL, len = 23;
    int min  = -13;
    int mx   = 33;
    arr      = new int[len];
    if (NULL == arr)
    {
        cout << "fail to new an array!" << endl;
        exit(-1);
    }
    srand(time(NULL));
    for (int i = 0; i < len; ++i)
        arr[i] = rand() % mx + min;
        // cout << rand() << endl;
    cout << "original arr: " << endl;
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    split_odd_even(arr,len);
    cout << "splited: " << endl;
    for (int i = 0; i < len; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}