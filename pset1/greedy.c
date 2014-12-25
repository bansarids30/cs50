#include<stdio.h>
#include<ctype.h>
#include<cs50.h>
#include<math.h>
int main(void)
{
    int nickel=0,quarter=0, penny=0, dime=0, amount=0;
    float change;
    
    do
    {
        printf("how much change is owed?");
        change=GetFloat();
        if(isalpha(change))
        {
            printf("retry");
            change=GetFloat();
        }
    }while(change<0);
    
    amount= (round(change*100));  
    
    quarter= amount/25;
    amount=amount%25;   
    
    nickel = amount/10;
    amount = amount%10;
    
    dime = amount/5;
    amount = amount%5;
    
    penny = amount/1;
    amount=amount%1;
    
    printf("%d\n", (quarter+nickel+penny+dime));
    return 0;
}
