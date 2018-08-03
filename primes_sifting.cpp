#include <iostream>
#include <set>
#include <vector>
#include <string.h>
using namespace std;

/**
 *  func   to get all the prime numbers in [0,max].
 *  prime  a vector to store the prime number.
 *  max    the upper bound of the range.
**/
void getPrimeNumSift(vector<unsigned> &prime, const unsigned max)
{
    unsigned i, j, cnt;
    bool *sift = new bool[max+1];          // true if its subscript is prime, 2^32 B = 4GB at most. 
    memset(sift, true, (max+1)*sizeof(bool));
    sift[0] = sift[1] = false;             // 0 and 1 are not prime.
    for (cnt=max-1, i=2; i <= (max+1)>>1; )// in range [2,(max+1)/2]
    {
        prime.push_back(i);               // i is the first prime in the rest part.
        for (j = i*i; j <= max; j += i)   // eliminate all numbers divisible by i.
        {
            if (sift[j])
            {
                --cnt;
                sift[j] = false;
            }
        }
        for(i += 1; i <= max/2+1 && !sift[i]; ++i); // search for the next prime number.
    }
    for(; i <= max; ++i)
        if(sift[i]) prime.push_back(i);  // the prime numbers in second half part.
}


int main(int argc, char const *argv[])
{
    int i, j, n, cnt, s, mx = 1200;
    vector <unsigned> p;
    getPrimeNumSift(p, mx);
}