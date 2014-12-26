#include<stdio.h>
#include<string.h>
#include <cs50.h>
int main(int argc, char* argv[])
{

if(argc!=2)
{
    printf("There should be only one command line argument");
    return 1;
}

for(int i=0;i<strlen(argv[1]);i++)
{
    char letter=argv[1][i];
    if(!((letter>=65 && letter<=90)||(letter>=97 && letter<=122)))
    {
        printf("you cannot have a number in argument\n");
        return 1;
    }  
}
string k=argv[1];
string p=GetString();
int klen=strlen(k);
int count=0;
for(int i=0;i<=strlen(p);i++)
{
    char akey=k[count % klen];
    if(p[i]>=97 && p[i]<=122)
    {
        printf("%c",(p[i]-97+akey-97)%26+97);
        count++;
    }
    else if(p[i]>=65 && p[i]<=90)
    {
        printf("%c",(p[i]-65+akey-65)%26+65);
        count++;
    }
    else//some other symbol
    {
        printf("%c",p[i]);
    }
}
printf("\n");

return 0;
}

