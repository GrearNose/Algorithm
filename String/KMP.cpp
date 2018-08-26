#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <iostream>
using  namespace std;

bool str_equal(const char s[], const char t[]);

void get_next(const char p[], const int len, int next_pos[])
{
    if (NULL == p || NULL == next_pos || 0 == len)
        return;
    /*
        Define the next_pos[j] as follow:
        next_pos[j] = 
                max{k| p[:k] == p[j-k:j]}, if such k exists;
                0, otherwise.
        N.B. when j == 0, it means that s[i] != p[j], the next
        two char to compare should be s[i+1] and p[0], the caller
        should deal with this case by just increase i, and keep
        j unchanged, thus here next_pos[0] is set to 0.

        ======== Algorithm =======
        And to find the max k is equivelant to make a str matching
        with p[1:] as the main str and, p[:] as the pattern str.
        And we use i and j as the indices(cursors) for p[1:] and p[:]
        respectively. When they mismatch at some point, one can compare
        the rest of the main str starting at current position, to the
        whole pattern str p[:], i.e. keep i unchanged, and set j to 0.
        However, some redundant comparision can be removed by setting
        j to next_pos[j] if there exist two sub strs in the head and
        tail of p[:j]. Thus, this definition is recursive and we can
        solve it bottom up.
    */
    int i = 1;       // index of p[1:]
    int j = 0;       // index of p[:]
    next_pos[0] = 0; // there are no identical substrs exist in the head 
    next_pos[1] = 0; // and the tail when the strlen <= 2.
    // calculate the next_pos by doing a str matching
    // with p[1:] as the main str, and p as the pattern str.
    while (i < len-1)
    {
        if (p[i] == p[j])
        {
            ++ i;
            ++ j;
            // found two identical substr: p[i-j:i] == p[:j],
            // (but cannot ensure p[i] == p[j]),
            // so when s[k] != p[i], the next two chars to compare
            // are s[k] and p[j], thus set next_pos[i] to j
            next_pos[i] = j;
        }
        else if (0 == j)
        {
            ++ i;            // N.B. update next_pos after '++i',
            next_pos[i] = 0; // as the prev one has already been updated.
        }
        else
            j = next_pos[j];
    }
}

int str_find(const char s[], const char p[], bool debug=false)
{
    if (NULL == s || NULL == p)
        return -1;

    int i, j;
    const int ln_s = strlen(s);
    const int ln_p = strlen(p);
    int next_pos[ln_p];

    get_next(p, ln_p, next_pos);

    if (debug)
    {
        printf("next pos: \n");
        for (int i = 0; i < ln_p; ++i)
            printf("%c ", p[i]);
        printf("\n");
        for (int i = 0; i < ln_p; ++i)
            printf("%d ", next_pos[i]);
        printf("\n");
        return 0;
    }

    i = j = 0;
    while(i < ln_s && j < ln_p)
    {
        if (s[i] == p[j])
        {
            ++ i;
            ++ j;
        }
        else if(j == 0)
            ++ i;
        else
            j = next_pos[j];
    }

    if (j == ln_p)
        return i-j;
    else
        return -1;
}

void test()
{
    int len = 1000000+1, test_num = 10000;
    char s[len];
    int test_cases[test_num][2];
    srand(time(NULL));
    printf("Generating the main str of len: %d ...\n", len);
    for (int i = 0; i < len; ++i)
    {
        s[i] = 'a' + rand() % 26;
        // s[i] = 'a' + rand() % 4;
    }
    s[len] = '\0';
    // printf("s:%s\n", s);
    printf("Generating the pattern strings ...\n");
    for (int i = 0; i < test_num; ++i)
    {
        int ix_s = rand() % (len - 3);
        int ln = 3 + rand() % (len - ix_s);
        test_cases[i][0] = ix_s;
        test_cases[i][1] = ln;
    }

    printf("testing the kmp ...\n");
    clock_t t0 = clock();
    for (int i = 0; i < test_num; ++i)
    {
        int ix = test_cases[i][0];
        int ln = test_cases[i][1];
        char t[ln+1];
        t[ln] = 0;
        memcpy(t,s+ix,ln*sizeof(char));

        // int ix1 = str_find(s, t, true);
        int ix1 = str_find(s, t);

        // printf("%d %d vs %d\n", i, ix, ix1);
        assert(ix == ix1 or str_equal(s+ix,t));
    }
    clock_t t = clock();
    printf("Passed all test cases, with time consumption: %ld\n",(t - t0));
}

bool str_equal(const char *s, const char *t)
{
    if (NULL == s || NULL == t)
        return false;
    while(0 != *s && 0 != *t && *s == *t)
    {
        ++ s;
        ++ t;
    }
    if (0 == *s || 0 == *t)
        return true;
    return false;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}