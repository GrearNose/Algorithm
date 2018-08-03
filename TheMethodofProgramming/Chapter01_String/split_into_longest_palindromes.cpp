#include <cstring>
#include <iostream>
using namespace std;

/*
Split the given str into several palindromes,
such that each one is as long as possible.
N.B. As two palindrome may overlap with each other,
they can not both be split with their longest length.
str: an array of type T;
split_border: ending ix of each palindrome;
len: length of the str.
*/
template <typename T>
void extract_longest_palindrome(T*str, bool*split_border, int len)
{
    if(str == NULL || len < 1)
        return;
    int i, j;
    int ix_odd, ix_even;
    int mx_odd = 0, mx_even = 0;

    // cout << "str: ";
    // for (i = 0; i < len; ++i)
    //     cout << str[i] << ' ';
    // cout << endl;

    for (i = 0; i < len; ++i)
    {
        // for odd-length palindrome.
        for (j = 1; (0 <= i-j) && (i+j < len); ++j)
        {
            if (str[i-j] != str[i+j])
                break;
        }
        if (j > mx_odd)
        {
            mx_odd = j;
            ix_odd = i;
        }

        // for even-length palindrome.
        for(j = 1; (0 <= i-j) && (i+j-1 < len); ++j)
        {
            if (str[i-j] != str[i+j-1])
                break;
        }
        if (j > mx_even)
        {
            mx_even = j-1;
            ix_even = i;
        }
    }

    // cout << "mx_odd,ix_odd:   " <<  mx_odd  << "," << ix_odd  << endl;
    // cout << "mx_even,ix_even: " <<  mx_even << "," << ix_even << endl;

    int begin, end;
    // if (2*mx_odd-1 > 2*mx_even)
    if (mx_odd > mx_even) // equally
    {
        // begin index of the longest palindrome to output.
        begin = ix_odd - mx_odd + 1;
        end   = ix_odd + mx_odd - 1; // end index.
    }
    else
    {
        begin = ix_even - mx_even;
        end   = ix_even + mx_even -1;
    }

    split_border[end] = true;
    int len_left      = begin; // left-side part of the longest palindrome.
    int len_right     = len - end - 1;// right-side part of the longest palindrome.
    extract_longest_palindrome(str,split_border,len_left);
    extract_longest_palindrome(str+end+1,split_border+end+1,len_right);
}

template <typename T>
void  split_into_longest_palindrome(T*str,int len)
{
    bool *split_border = new bool[len], within = true;
    extract_longest_palindrome(str,split_border,len);
    for (int i = 0; i < len; ++i)
        cout << str[i] << " ";
    cout << ":" << endl;
    for (int i = 0; i < len; ++i)
    {
        while (!split_border[i])
            cout << str[i++] << ",";
        cout << str[i] << endl;
    }
}

void test()
{
    // char s[] = "habbafgh";
    // char s[] = "babbafgh";
    // split_into_longest_palindrome(s,strlen(s));
    int s[] = {2,23,1,23,2,2,3,4,3};
    split_into_longest_palindrome(s,9);

}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}