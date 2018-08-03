#include <cstring>
#include <iostream>
using namespace std;

/*
Judge a whether given str is a palindrome
by comparing chars from its two ends toward
its center.
*/
bool isPalindrome(char*str, int n)
{
    if (str == NULL || n < 1)
    {
        return false;
    }
    const char *front, *end;
    front = str;
    end   = str + n - 1;
    while(front < end)
    {
        if(*front != *end)
            return false;
        ++ front;
        -- end;
    }
    return true;
}

/*
Judge whether a given str is a palindrome
by comparing chars from its center towards
its two ends.
*/
bool isPalindrome2(char*str,int n)
{
    if (str == NULL || n < 1)
    {
        return false;
    }
    int m = ((n>>1)-1) >= 0 ? (n>>1)-1 : 0;
    char * first = str + m;
    char *second = str + n - 1 - m;
    while (first >= str)
    {
        if (*first != *second)
        {
            return false;
        }
        --first;
        ++ second;
    }
    return true;
}


void test()
{
    char s[] = "aba";
    cout << s << ": " << isPalindrome(s,strlen(s)) << endl;
    cout << s << ": " << isPalindrome2(s,strlen(s)) << endl;
    cout << true;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}