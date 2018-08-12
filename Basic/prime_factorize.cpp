#include <iostream>
#include <map>
#include <assert.h>
using namespace std;

/*
 *  Func factorize a given num n with a set of prime.
 *  n  the number to factorize.
 *  return  a map of <prime_factor, occurance> describing the factorization.
*/
template<typename T>
std::map<T, T> prime_factorize(T n)
{
    assert(n > 0);
    T factor, cnt;
    std::map<T, T> occurance;
    for (factor = 2; factor*factor < n; ++factor)
    {
        for(cnt=0; n%factor==0; ++cnt)
            n /= factor;
        if(cnt > 0)
            occurance[factor] = cnt;
    }
    if (n > 1)
        occurance[n] = 1;
    return occurance;
}

void test(int upper)
{
    bool passed = true;
    for (int j = 1; j <= upper; ++j)
    {
        int n = j, prod = 1;
        std::map<int, int> map = prime_factorize(n);
        std::map<int, int>::iterator itr;
        // printf("Factors of %d:\n", n);
        for(itr=map.begin(); itr != map.end(); ++itr)
        {
            // cout << itr->first << ": " << itr->second << ", ";
            for (int i = 0; i < itr->second; ++i)
                prod *= itr->first;
        }
        // cout << endl << "prod: " << prod << endl;


        if(prod != n)
        {
            // printf("Wrong!\n");
            passed = false;
        }
        // else
        //     printf("Correct!\n");
    }
    if (passed)
        printf("All test passed!\n");
    else
        printf("Does not pass all test!\n");
}

int main(int argc, char const *argv[])
{
    test(23335);
    return 0;
}