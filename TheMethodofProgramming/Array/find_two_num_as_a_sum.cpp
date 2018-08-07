#include <algorithm>
#include <ctime>
#include <vector>
#include <iostream>

#define N 13
using namespace std;

/*
In an ascendingly sorted array, there may be some pairs of elements summing up to a
certain num, find out all these pairs of elements.
args
arr: the head address of the array to search, sorted ascendingly;
len: length of the array to search.
sum: sum of the two num fo search.
pair_indices: a vector to record the indices of all the possible pairs of such num.
*/
template <typename T>
void find_two_num_with_a_sum(T*arr,int len, T sum, vector<pair<int,int>>*pair_indices)
{
    // cout << "len: " << len << endl;
    if (NULL == arr or len < 1 or NULL == pair_indices)
        return ;

    int i, j;
    pair<int,int> p;
    for(i = 0, j = len-1; i < j; )
    {
        T s = arr[i] + arr[j];
        if (s == sum)
        {
            int ix1, ix2;
            for(ix1 = i; arr[i] == arr[ix1]; ++ix1)
            {
                for(ix2 = j; arr[j] == arr[ix2]; --ix2)
                {
                    p.first  = i;
                    p.second = j;
                    pair_indices->push_back(p);
                    // printf("found at (%d,%d)\n", i,j);
                }
            }
	    i = ix1;
	    j = ix2;
        }
        else if(s < sum)
            ++ i;
        else // s > sum
            -- j;
    }
}

void test()
{
    unsigned i, j, arr[N], mx = 33;
    vector<pair<int,int>> pair_indices;
    srand(time(NULL));
    for (i = 0; i < N; ++i)
        arr[i] = rand() % mx;

    sort(arr,arr+N);

    cout << "arr: ";
    for (i = 0; i < N; ++i)
        cout << arr[i] << " ";

    i = j = 0;
    while(i == j)
    {
        i = rand() % N;
        j = rand() % N;
    }
    unsigned sum = arr[i] + arr[j];
    printf("\nsum: %d = %d + %d\n", sum, arr[i], arr[j]);
    find_two_num_with_a_sum(arr, N, arr[i] + arr[j], &pair_indices);

    if(pair_indices.size() > 0)
    {
        printf("Found %lu pairs: ", pair_indices.size());
        for (i = 0; i < pair_indices.size(); ++i)
        {
            pair<int,int> p;
            p = pair_indices[i];
            int ix1 = p.first;
            int ix2 = p.second;
            if (sum != arr[ix1] + arr[ix2])
            {
                printf("Incorrect pair: (%d,%d)\n", ix1, ix2);
                continue;
            }
            printf("(%u,%u) ", arr[ix1], arr[ix2]);
        }
        cout << endl;
    }
    else
    {
        printf("Wrong! Found none !\n");
    }
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}
