#include<stdio.h>
#include<string.h>
#include <cs50.h>
int main(void)
{
string s="abc34fr6";
for(int i=0;i<strlen(s);i++)
{
    if(!((s[i]>=65 && s[i]<=90)||(s[i]>=97 && s[i]<=122)))
    {
        printf("you have a number here\n");
    }
}
}

