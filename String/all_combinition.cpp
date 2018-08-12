#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

/*
choose num elems from the set and give output the combinitions
of them, i.e. C(size,num) combinitions.
set: the set of elem to choose;
indices: auxiliary arr to record the indices of chosen elems;
size: size of the set;
num: num of elems to choose;
d: index of the current one, among the num elems to choose.
*/

template<typename T>
void combinition(T *set, int *indices, int size, int num, int d)
{
    int i,j;
    if(d > num || num > size) // invalid
        return;
    i = d==1? 0:indices[d-2]+1;
    for (; i < size; ++i)
    {
        if(d < num)
        {
            indices[d-1] = i;
            combinition(set,indices,size,num,d+1);
        }
        else // d == num
        {
            for(j = 0; j < num-1; ++j)
                cout << set[indices[j]];
            cout << set[i] << endl;
        }
    }
}

/*
Generate all of the combinition of a given set of elems,
i.e. with the amount of each as C(n,1), C(n,2),...,C(n,n).
set: the set of elems to choose;
n:   size of the set.
There are (2^n)-1 combinitions.
e.g. all combinitions of 'ABC': A,B,C,AB,AC,BC,ABC.
*/
template<typename T>
void allCombinitions(T*set,int n)
{
    static int *indices = new int[n];

    for(int num=1; num<=n; ++num)
    {
        combinition(set,indices,n,num,1);
    }
}

void test()
{
    char s[] = "ABCD";
    allCombinitions(s,strlen(s));
    // int s[] = {1,2,3};
    // allCombinitions(s,3);
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}