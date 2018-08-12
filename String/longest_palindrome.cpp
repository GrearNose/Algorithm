#include <cstring>
#include <iostream>
using namespace std;

/*
To find the length of the longest palindrome
in the given str, using a center-method,i.e.
fix a center position and then find the palindrome
at its two ends.
str: the given str;
n: length of the given str.
*/
int longestPalindrome(char*str,int n)
{
    if (str == NULL || n < 1)
    {
        return 0;
    }

    int i, j, len, max = 0;
    // i, center of the palindrome.
    for (i = 0; i < n; ++i)
    {
        // cout << "---- i: " << i << endl;
        // len of the palindrome is odd.
        for (j = 0; (i-j >= 0) && (i + j < n); ++j)
        {
            if (str[i-j] != str[i+j])
            {
                break;
            }
        }
        len = 2 * (j-1) + 1;
        if (len > max)
        {
            max = len;
        }
        // cout << "j1: " << j << endl;

        // len of the palindrome is even.
        for(j = 0; (0 <= i-j) && (i+j+1 < n); ++j)
        {
            if (str[i-j] != str[i+j+1])
            {
                break;
            }
        }
        len = 2 * (j-1) + 2;
        if (len > max)
        {
            max = len;
        }
        // cout << "j2: " << j << endl;
    }

    return max;
}

void test()
{
    // char s[] = "cdc";
    char s[] = "abcdcabcddcba";
    cout << s << "\nlen of longest palindrome: "\
     << longestPalindrome(s,strlen(s)) << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}