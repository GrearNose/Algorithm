#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm> 
using namespace std;

int nums[101], mx[10001];

template <typename T>
long max_sum_inc_seq(const T nums[], int ln)
{
    if (NULL == nums || ln <= 0)
        return -1;
    int i, j;
    // int *mx = new int[ln];
    int mx[ln];
    memset(mx,0,sizeof(int)*ln);
    
    mx[0] = nums[0];
    for(i = 1; i < ln; i++)
    {
        for(j = 0; j<i; j++)
        {
            if(nums[i] > nums[j])
                mx[i] = max(mx[i],mx[j] + nums[i]);
        }
        mx[i] = max(mx[i], nums[i]);
    }

    long MAX = 0;
    for(i = 0; i < ln; i++)
        if (mx[i] > MAX)
            MAX = mx[i];

    // delete(mx);

    return MAX;
}

void test0()
{
    int n,i;
    while( scanf("%d",&n)!=EOF && n!=0)
    {
        for(i = 0; i < n; i++)
            scanf("%d", &nums[i]);
        long mx = max_sum_inc_seq(nums,n);
        printf("%ld\n", mx);
    }
}

void test1()
{
    int n = 10, i;
    int mn = 3, mx = 13;
    srand(time(NULL));
    printf("arr: ");
    for(i = 0; i < n; i++)
    {
        nums[i] = mn + rand() % mx;
        printf("%d ", nums[i]);
    }
    long  mx_sum = max_sum_inc_seq(nums,n);
    printf("\nmax_sum: %ld\n", mx_sum);
}

int main(int argc, char const *argv[])
{
    test1();
    return 0;
}