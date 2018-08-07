#include <algorithm>
#include <ctime>
#include <vector>
#include <iostream>

#define N 13
using namespace std;

/*
In an ascendingly sorted array, there may be some pairs of elements summing up
to a certain num, find out all these pairs of elements. The algorithm is uses
two pointers to search from two ends of the array toward the middle, during
which the key is how to update the pointers:
for briefness, assume we use two subscript variables i and j instead of pointers,
i starts from the left end, and j starts from the right end of the array, there
are 3 cases to consider:
   1. arr[i] + arr[j] < sum, it means that these two elements are too small,
      we need to increase i to get a larger pair, such that we may get closer
      or find the pair exactly sum up to the given sum;
   2. arr[i] + arr[j] > sum, it means that they are two large, we need to
      decrease j to get a smaller pair;
   3. arr[i] + arr[j] == sum, then one pair has been found. Be careful that
      there may be some other elements equal to them, then they can make a pair,
      and we need to find out all these pairs. In this case, we can use two
      loop to find out all these pairs, one iterates through all the elements
      equal to arr[i] (including arr[i]), and the other arr[j](including arr[j]).
complexity: in normal case, when the number of duplicate pairs that add up to the 
  given sum is very small, the time complexity is o(n), in the worse case when
  all elements in the array are equal, then there are n*(n-1) pairs, then the
  complexity is o(n^2)
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
