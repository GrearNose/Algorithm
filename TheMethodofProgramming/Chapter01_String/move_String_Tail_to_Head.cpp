#include <string.h>
#include <stdio.h>

/*
Shift a given str to the left by one char,
e.g. "abc" -> "bca".
*/
void str_left_shift_one(char*s,int n)
{
    char t = s[0];
    for(int i=0; i<n; ++i)
        s[i] = s[i+1];
    s[n-1] = t;
}

/*
Move the first m chars in a str to the tail (in place)
by left shifting the given str. O(n*m).
e.g. move the first 3 chars of "abciii" to its tail,
then the result is "iiiabc".
*/
void leftRoteString(char*s,int n, int m)
{
    while(m--)
    {
        str_left_shift_one(s,n);
    }
}

/*
Reverse the order the substr of the given str.
e.g. reverse the substr "abc" of "abcdef",
then the result is "cbadef".
*/
void reverseString(char*s,int from, int to)
{
    while(from < to)
    {
        char t = s[from];
        s[from++] = s[to];
        s[to--] = t;
    }
}

/*
Move the first m chars in a str to the tail (in place)
by first reversing its two substr and then the whole str. O(n).
e.g. move the first 3 chars of "abciii" to its tail,
then the result is "iiiabc".
*/
void leftRoteString_reversing(char*s,int n, int m)
{
    m %= n;
    reverseString(s,0,m-1);
    reverseString(s,m,n-1);
    reverseString(s,0,n-1);
}

/*
test the funcs above.
*/
int test()
{
    // char s1[] = "I am a student.";
    char s1[] = "I am a good student.";
    char s2[] = "I am a good student.";
    // char s2[] = "I am a bad student.";
    // char s[] = "student was her.";
    // str_left_shift_one(s,strlen(s));
    leftRoteString(s1,strlen(s1),7);
    leftRoteString_reversing(s2,strlen(s2),7);
    printf("%s\n",s1);
    printf("%s\n",s2);
}

int main()
{
    test();
}