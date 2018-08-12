#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

/*
Convert a str into a int, invalid inputs are considered.
*/
int str2int(char*str)
{
    static const int MAX_INT = (int)((unsigned)~0 >> 1);
    static const int MIN_INT = -(int)((unsigned)~0 >> 1)-1;

    int sign = 1;
    unsigned n = 0;

    // cout << str << endl;

    while(isspace(*str))
        ++str;
    if (*str== '+' || *str == '-')
    {
        // cout << "Found sign!" << endl;
        if(*str == '-')
            sign = -1;
        ++ str;
    }

    // cout << "sign: " << sign << endl;
    // cout << str << endl;

    while(isdigit(*str))
    {
        int c = *str - '0';
        // cout << c << ", ";
        if (sign > 0 && n > MAX_INT/10 || (n==MAX_INT/10 && c > MAX_INT%10) )
        {
            return MAX_INT;
        }
        else if(sign < 0 && n > (unsigned)MIN_INT/10 || \
            (n==(unsigned)MIN_INT/10 && c > (unsigned)MIN_INT%10))
        {
            return MIN_INT;
        }
        n = n * 10 + c;
        ++ str;
    }
    return sign > 0 ? n : -n;
}

void test()
{
    // char s[] = "-1213";
    // char s[] = "1213";
    // char s[] = "9w47532-5";
    // char s[] = "-9w47532-5";
    // char s[] = "10522545459";
    char s[] = "-10522545459";
    cout << str2int(s) << endl;
    // cout << "'\\0' is digit: " << isdigit('\0') << endl;
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}