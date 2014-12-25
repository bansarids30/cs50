#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
int main(void)
{
int i,j,k,height;

do
{
height=GetInt();
if(isalpha(height)){
printf("retry");
height=GetInt();
}
}
while (height<=0 || height >=23);

for (i=1;i<=height;i++)
{
    for(j=height-i;j>0;j--)
    {
    printf(" ");
    }
    for(k=1;k<=i+1;k++)
    {
    printf("#");
    }
printf("\n");
}
}
