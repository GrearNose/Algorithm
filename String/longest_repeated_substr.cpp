#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int len_common_prefix(const char *s, const char *t)
{
    if (NULL == s || NULL == t)
        return 0;
    int i = 0;
    while(0 != s[i] && s[i] == t[i])
        ++ i;
    return i;
}

int str_cmp(const void *p, const void *q)
{
    // srand(time(NULL));
    // return rand() % 3 - 1;
    // return strcmp((const char*)p, (const char*)q);
    // return strcmp(*(char**)p, *(char**)q);
    char *p1 = (char*)p;
    char *p2 = (char*)q;
    while(*p1 && *p1 == *p2)
    {
        ++p1;
        ++p2;
    }
    return *p1 - *p2;
}

int pstrcmp(const void * p, const void * q)
{
    return strcmp(*(char**)p, *(char**)q);
}

bool longest_repeated_substr(const char *s, int len, int &start_ix, int &len_substr)
{
    if (NULL == s || len <= 0)
        return false;
    printf("%s\n", s);
    printf("len:%d\n", len);
    const char *suffixes[len];
    for (int i = 0; i < len; ++i)
    {
        suffixes[i] = &(s[i]);
        printf("%s\n", suffixes[i]);
    }
    // sort(suffixes, suffixes+len, str_cmp);
    // sort(suffixes, suffixes+len);
    // qsort(suffixes,len,sizeof(char*),str_cmp);
    qsort(suffixes,len,sizeof(char*),pstrcmp);

    for(int i = 0; i < len; ++i)
    {
        printf("%s\n", suffixes[i]);
    }
    start_ix   = -1;
    len_substr = 0;
    for (int i = 0; i < len-2; ++i)
    {
        const char *p = suffixes[i];
        const char *q = suffixes[i+1];
        printf("%s vs. %s, %d\n", p, q, strcmp(p, q));
        int ln = len_common_prefix(p,q);
        if (ln > len_substr)
        {
            len_substr = ln;
            start_ix = p - s;
        }
    }
    if (0 == len_substr)
        return false;
    else
        return true;
}

void test()
{
    const char *s = "asdofi";
    int len = strlen(s);
    int start_ix = 0, len_substr = 0;
    longest_repeated_substr(s,len,start_ix,len_substr);
    printf("ix:%d, len:%d\n", start_ix, len_substr);
    for (int i = start_ix; i < start_ix + len_substr; ++i)
    {
        putchar(s[i]);
    }
    printf("\n");
}

void test2()
{
    const char *s = "asljdfg";
    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", str_cmp(s,s));
    }
}

int main(int argc, char const *argv[])
{
    test();
    // test2();
    return 0;
}