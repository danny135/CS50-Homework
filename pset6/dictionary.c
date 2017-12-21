/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

node* hashtable[BUCKETS];
bool loaded;
int words;

int hash(const char* word)
{
    unsigned long hash = 1337;
    
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        hash = hash * LENGTH + tolower(word[i]);
    }

    return (int)(hash % BUCKETS);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* cursor = hashtable[hash(word)];
    
    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {

            return true;
        }
        
        cursor = cursor->next;
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    int index;
    words = -1;

    while(!feof(file))
    {
        
        node* new_node = malloc(sizeof(node));
        fscanf(file, "%s", new_node->word);
        
        index = hash(new_node->word);

        if (hashtable[index] != NULL)
        {   
            new_node->next = hashtable[index];
        }

        hashtable[index] = new_node;
        
        words++;
        
        if (ferror(file))
        {
            fclose(file);
            return false;
        }
    }
    
    fclose(file);
    loaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (!loaded) return 0;
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < BUCKETS; i++)
    {
        //Get the first bucket of the index
        node* cursor = hashtable[i];
        
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    
    return true;
}
