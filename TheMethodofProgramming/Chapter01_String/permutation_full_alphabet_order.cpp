#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

/*
  Description
  To generate a full permuation of a given string in alphabet order.
  N.B. The original str should be in ascending alphabet order.
*/

template <typename T>
void myReverse(T*from,T*to) // an simple implementation of reverse.
{
    // cout << (to-from)/sizeof(T) << endl;
    while(from<to) {
        T tmp = *from;
        *(from++) = *to;
        *(to--) = tmp;
    }
}

bool nextPermutation(char*perm,int num)
{
    int i, j; // find out the last ix that starts a ascending order.
    for (i = num-2; (i >= 0) && perm[i]>=perm[i+1]; --i);
    if (i < 0)
        return false;
    // to find the smallest num perm[j] satisfying perm[j] > perm[i]:
    // As perm[i:] is in descending order, just to find the first
    // one from the rear.
    for (j = num-1; (i<j) && (perm[j]<=perm[i]); --j);
    swap(perm[i],perm[j]);
    // myReverse(perm+i+1,perm+num-1); // for the one defined in this file.
    reverse(perm+i+1,perm+num); // for the one from STL.
    return true;
}

void calcFullPermutation(char*perm,int num)
{
    do
    {
        cout << perm << endl;
    } while (nextPermutation(perm,num));
}


int main(int argc, char const *argv[])
{
    char s[] = "ABC";
    // char s[] = "ABCEF";
    // when the string is in descending alphabet order, the func only
    // outputs one permut and then expires.
    // myReverse(s,s+strlen(s)-1); // for the one defined in this file.
    // reverse(s,s+strlen(s));     // for the one from STL.
    // cout << "reversed str: " << s << endl;
    calcFullPermutation(s,strlen(s));
    return 0;
}