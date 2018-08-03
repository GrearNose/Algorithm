#include <iostream>
#include <algorithm>
using namespace std;

double mean(long *arr, long n,int m = 2)
{
    double mean =0;
    double sum = 0;
    int i = 0;
    for (i = 0; i < n; ++i)
    {
        sum += arr[i];
        if (i > 0 && i % m ==0)
        {
            mean += sum / n; // avoid overflow.
            sum = 0;
        }
    }
    mean += sum / n;

    return mean;
}

int main(int argc, char const *argv[])
{
    int i, size = 10;
    long *arr = new long[size];
    for (i = 0; i < size; ++i)
        arr[i] = 3*i + 3;
    double m = mean(arr,size);
    cout << "mean: " << m << endl;
    return 0;
}