#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char* argv[])
{
    bool keySuccessful = false;
    int key = 0;
    string text = "";
    
    // Get input
    // The number of command line args submitted was incorrect. 
    if(argc != 2)
    {
        printf("You didn't submit a valid encryption key.\n");
        return 1;
    }
    else
    {
        // Key needs to be converted from string to int
        key = atoi(argv[1]);
        keySuccessful = true;
    }
      
    // Read user input
    text = GetString();
    int length = strlen(text);
    for(int i = 0; i < length; i++)
    {
        // Process characters
        if(isalpha(text[i]))
        {
            // Work with lower case characters
            if(islower(text[i]))
            {
                printf("%c", ((((text[i] - 97)+key)%26)+97));
            }
            // Work with upper case characters
            else
            {
                printf("%c", ((((text[i] - 65)+key)%26)+65));
            }
        }
        // "Mirror" all other input to the result string w/out processing
        else
        {
            printf("%c", text[i]);
        }
    }
    // Be a good citizen and exit cleanly. 
    printf("\n");
    return 0;  
}
