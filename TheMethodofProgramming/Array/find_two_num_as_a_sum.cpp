#include <algorithm>
#include <ctime>
#include <iostream>
#define N 23
using namespace std;

/*
Find out two num in an ascendingly sorted array that will sum up to a given num.
args
arr: the head address of the array to search, sorted ascendingly;
len: length of the array;
sum: sum of the two num fo search.
*/
template <typename T>
bool find_two_num_with_a_sum(T*arr,int len, T sum, int &n1, int &n2)
{
    if (NULL == arr or 0 == len)
        return false;

    int i, j;
    for(i = 0, j = len-1; i < j; )
    {
        T s = arr[i] + arr[j];
        if (s == sum)
        {
            n1 = i;
            n2 = j;
            return true;
        }
        else if(s < sum)
            ++i;
        else // s > sum
            --j;
    }
    return false;
}

void test()
{
    int i, j, arr[N], mx = 33;
    srand(time(NULL));
    cout << "arr: ";
    for (i = 0; i < N; ++i)
    {
        arr[i] = rand() % mx;
        cout << arr[i] << " ";
    }

    sort(arr,arr+N);

    i = j = 0;
    while(i == j)
    {
        i = rand() % N;
        j = rand() % N;
    }

    int ix1, ix2;
    ix1 = ix2 = 0;
    printf("\nsum: %d\n", arr[i] + arr[j]);
    find_two_num_with_a_sum(arr, N, arr[i] + arr[j], ix1, ix2);

    if (arr[ix1] + arr[ix2] == arr[i] + arr[j])
    {
        cout << "correct!" << endl;
    }
    else
    {
        printf("Wrong!\n");
        printf("ix correct vs found: (%d,%d) vs (%d,%d)\n", i,j,ix1,ix2);
    }
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}