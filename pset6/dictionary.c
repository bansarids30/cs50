#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

int wordsloaded = 0;

typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;
     
node* root;
int getkey(char c)
{
    if(c=='\'')
        return 26;
    return (c-'a');
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{   
    node* ptr = root;
    char c;    
    int key;
    for (int i=0;i<strlen(word);i++)
    {
        if(islower(word[i]) || word[i]=='\'')
            c = word[i];
        else
            c = (word[i] + 32);  
              
        key=getkey(c);
        if(ptr->children[key] == NULL)
                return false;
        if(i == (strlen(word)-1))//last letter
        {   
            ptr=ptr->children[key];            
            if(ptr->is_word==true)
            {
                return true;
            }
            else
            {
                return false;
            }
        } 
        else if(i<=strlen(word))
        {           
           ptr=ptr->children[key];
        }          
    }
    return false;    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    root = malloc(sizeof(node));
    int c = 0;
    node* ptr = NULL;
    
    while(fgetc(dict) != EOF)
    {
        fseek(dict, -1, SEEK_CUR);// we use -1 here as we do in while

	    // Set the temp pointr to the root
        ptr = root;

        for (c = fgetc(dict); c != '\n'; c = fgetc(dict))
        {    
            // Check for apostrophes
            if (c == '\'')
            {
                // Set it to one past the highest letter, z
                c = 'z' + 1;
            }

            // Check if the character exists in the trie
            if (ptr->children[c - 'a'] == NULL)
            {
		        // If the character does not exist, malloc a new node
                ptr->children[c - 'a'] = malloc(sizeof(node));
		        ptr = ptr->children[c - 'a'];
                
	        }
	        else
            {
		        // to the node that is already present
                ptr = ptr->children[c - 'a'];
	        }
	    }
        ptr->is_word = true;
        wordsloaded++;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordsloaded;//we have already kept track in load function 
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool freeNode(node* ptr)
{
    for(int j = 0; j < 27; j++)
    {
        if(ptr->children[j] != NULL)
        {
            freeNode(ptr->children[j]);  
        }      
	}
    free(ptr);
    return true;
}

bool unload(void)
{
    return freeNode(root);
}
