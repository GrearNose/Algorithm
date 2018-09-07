#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/*
    Given a set of addens and their max occurance, figure out
    the number of different sum they can sum up to.
    Args:
    addens: a an array of the addens;
    num: the max occurance of the corresponding adden in addens;
    len: the len the these two array.
    return: the number of the different sum these addens can sum up to.
*/
int sum_cnt(const int addens[], const int num[], const int len)
{
    if (NULL == addens || NULL == num || len <= 0)
        return 0;
    // records the different sum of a certain combination of addens.
    set<int> com;
    // initialize with 0, as 0 is a possible combination.
    com.insert(0);

    // put the first type of addens into the set.
    for(int i = 1; i <= num[0]; i++)
        com.insert(i * addens[0]);

    // for each of the rest n-1 types of addens.
    for(int i = 1; i < len; i++)
    {
        vector<int> sum_new;
        for(int s : com) // based on each of the existing combination,
        {
            // make a new combinition by adding j addens of the i-th type.
            for(int j = 1; j <= num[i]; j++) 
            {
                int trial = s + j * addens[i];
                // if this new combination yields a new sum, write it down.
                if(com.end() == com.find(trial))
                    sum_new.push_back(trial);
            }
        }
        if (sum_new.size() > 0)
        {
            for(int s: sum_new)
                com.insert(s);
        }
    }
    return com.size();
}

void test()
{
    int test_num = 10;
    int len = 5;               // number of counterweight.
    int addens[10] = {0};// addens of each type of counterweight
    int num[10] = {0};   // number of each type of counterweight.
    int mn = 1, mx = 8;
    srand(time(NULL));
    for(int j = 0; j < test_num; ++j)
    {
        cout << "addens: ";
       for(int i = 0; i < len; i++)
       {
           addens[i] = rand() % mx + mn;
           cout << addens[i] << " ";
       }
       cout << endl << "nums: ";
       for(int i = 0; i < len; i++)
       {
           num[i] = rand() % 2 + 1;
           cout << num[i] << " ";
       }
        cout << endl << "count of sum: " << sum_cnt(addens,num,len) << endl << endl;
    }    
}


int main(int argc, char const *argv[])
{
    test();
    return 0;
}
