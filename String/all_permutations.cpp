#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

/*
choose num elems from the set and give output the permutations
of them, i.e. A(size,num) arrangements.
set: the set of elem to permuate;
indices: auxiliary arr to record the indices of chosen elems;
available: auxiliary bool arr to record the availability of elems,
size: size of the set;
num: num of elems to choose and arrange;
d: index of the current one to choose, among the num elems to permutate.
*/
template<typename T>
void permutation(T *set, int *indices, bool*available, int size, int num, int d)
{
    int i,j;
    if(d > num || num > size) // invalid
        return;

    for (i = 0; i < size; ++i)
    {
        if (!available[i])
            continue;
        if(d < num)
        {
            available[i] = false;
            indices[d-1] = i;
            permutation(set,indices,available,size,num,d+1);
            // free the allocation to the current bits.
            available[i] = true;
        }
        else // d == num
        {
            for(j=0; j<num-1; ++j)
                cout << set[indices[j]];
            cout << set[i] << endl;
        }
    }
}

/*
Generate all of the permutation of a given set of elems,
i.e. with the amount of each as A(n,1), A(n,2),...,A(n,n).
set: the set of elems to permutate;
n:   size of the set.
*/
template<typename T>
void allPermutations(T*set,int n)
{
    static bool *available = new bool[n];
    static int *indices = new int[n];
    for (int i = 0; i < n; ++i)
        available[i] = true;

    for(int num=1; num<=n; ++num)
    {
        permutation(set,indices,available,n,num,1);
    }
}

void test()
{
    // char s[] = "ABC";
    // allPermutations(s,strlen(s));
    int s[] = {1,2,3};
    allPermutations(s,3);
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}