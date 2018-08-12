#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <vector>
#include <string.h>
#include <assert.h>
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
    for (cnt=max-1, i=2; i <= max/2+1; )
    {
        prime.push_back(i);               // start with 2.
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

/**
 *  func   LCM(Least Common Multiple) of a set of numbers.
 *  arr    the array of the given numbers.
 *  n      the count of the given numbers.
 *  prime  the first m prime numbers (auxiliary),
 *         and it should contains all factors of nums in arr.
 *  m      count of prime numbers in prime.
 *  mod    the module to mod (in case that lcm is too large).
 *  return the LCM of the given numbers.
 *  ALGORITHM:
 *   Just like cal LCM manually, the given set of nums are dividen iteratively
 *   by a prime factor util all of them turn into 1, and at last LCM is the prod of all these factors.
 *   N.B. A prime factor may appear more than once.
*/
long LCM(unsigned *arr, unsigned n,  vector<unsigned> &prime, unsigned m, unsigned mod=0)
{
    long lcm = 1;
    bool divided;
    int i, j, mx;
    // cout << "\nn:"<<n << " m:"<<m<<endl;
    assert(mod >= 0);
    for (j = 0, mx = prime[m-1]; j < m && prime[j] <= mx; )
    {
        divided = false;
        for ( i = 0, mx = arr[0]; i < n; ++i) // use prime as divisor to divide all nums.
        {
            if(arr[i] % prime[j] == 0)
            {
                if(!divided)
                {
                    if (mod)
                        lcm = lcm*prime[j] % mod;
                    else
                        lcm *= prime[j];
                    divided = true;
                }
                arr[i] /= prime[j];
            }
            if (arr[i]> mx) mx = arr[i];
        }
        // New nums may have been generated if any num was dividen,
        // in that case use the prime as divisor again in next iter;
        // otherwise try the next prime as a new divisor.
        j = divided? 0 : j + 1;
    }
    return lcm;
}

/*
*   func   to get the LCM of a set of numbers, using the set 
*          to avoid duplication and thus the unnecessary computation.
*   num    the given set of numbers.
*   prime  the first m prime numers (auxiliary).
*   m      the count of prime numbers.
*/
long LCM_v2(set<unsigned>&num, vector<unsigned> &prime, unsigned m)
{
    long lcm;
    set<unsigned> tmp;
    unsigned i, j, q, dv[1000], cnt = 0;
    for (j = 0; j < m && prime[j] <= *num.rbegin() && num.size() > 1; )
    {    // prime nums in ascending order
        bool divided = false;
        set<unsigned>::reverse_iterator it, it2;
        // use in reverse order to get update value with higher chance of duplication.
        for (it = num.rbegin(); it != num.rend(); ++it)
        {
            if(*it % prime[j] == 0)
            {
                if(!divided)
                {
                    divided = true;
                    dv[cnt++] = prime[j];
                }
                q = *it / prime[j];
                // num.erase((++it).base());// not know why this will cause error.
                it2 = it;               // use it2 to avoid error.
                ++ it2;
                num.erase(it2.base());
                if(q > 1)
                {
                    if (q % prime[j])
                        num.insert(q);
                    else
                        tmp.insert(q); // put it into tmp to avoid being dividen again.
                }
            }
        }
        if(!tmp.empty())
        {
            for(it=tmp.rbegin(); it!=tmp.rend(); ++it)
                num.insert(*it);
            tmp.clear();
        }

        j = divided? 0 : j + 1;
    }
    for (i = 0, lcm = 1; i < cnt; ++i) lcm *= dv[i]; // prod of all the dividen
    if(num.size() == 1) lcm *= *(num.begin());
    return lcm;
}


void test_LCM()
{
    int i, lb = 1, ub = 10, cnt = 5, mx = 1000;
    vector<unsigned> prime;
    unsigned int *s = new unsigned int[cnt];
    // void getPrimeNumSift(vector<unsigned> &prime, const unsigned max)
    getPrimeNumSift(prime, mx);

    srand(time(NULL));
    for (i = 0; i < cnt; ++i)
    {
        s[i] = lb + rand() %(ub-lb+1);
        printf("%u,", s[i]);
    }
    printf("\n");

    // long LCM(unsigned *arr, unsigned n,  vector<unsigned> &prime, unsigned m)
    long lcm = LCM(s, cnt, prime, prime.size());
    printf("LCM: %lu\n", lcm);
}


int main(int argc, char const *argv[])
{
    test_LCM();
    return 0;
}