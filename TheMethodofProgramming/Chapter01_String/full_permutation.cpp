#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

void CalcFullPermutation(char*perm,int from, int to)
{
    if (to <= 0)
    {
        return;
    }
    if (from == to)
    {
        for (int i = 0; i < to; ++i)
        {
            cout << perm[i];
        }
        cout << endl;
    }
    else
    {
        for (int j = from; j < to; ++j)
        {
            swap(perm[j],perm[from]);
            CalcFullPermutation(perm,from+1,to);
            swap(perm[j],perm[from]); // restore the the original form.
        }
    }
}

int main(int argc, char const *argv[])
{
    char s[10] = "ABC";
    cout << strlen(s) << endl;
    CalcFullPermutation(s,0,strlen(s));
    return 0;
}