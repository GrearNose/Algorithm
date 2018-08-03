#include <string.h>
#include <stdio.h>

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
Reverse the order of all words in a sentence
but not the letters within each word.
e.g. 
"I am a student." -> "student. a am I"
*/
void reverseByWords(char*s,int n)
{
    int from, to;
    for(from=to=0; to<n; ++to)
    {
        if(' ' == s[to])
        {
            reverseString(s,from, to-1);
            from = to+1;
        }
    }
    reverseString(s,from,n-1);
    reverseString(s,0,n-1);
}


/*
test the funcs above.
*/
int test()
{
    char s[] = "I am a student.";
    // char s[] = "student was her.";
    reverseByWords(s,strlen(s));
    printf("%s\n",s);
}

int main(int argc, char const *argv[])
{
    test();
    return 0;
}