// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if (table[hash(word)] != NULL)
    {
        // Hash the word to get hash value
        node *cursor = table[hash(word)];
        // at that has value, keep moving towards the next linked list until NULL is found
        while (cursor != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
            return true;
            }
            else
            {
            cursor = cursor->next;
            }
        }
    }
    // If found, reutrn true
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // // First Approach: Sorting by first dew letters
    // int hash_value = 0;
    // int first_letter = 0;
    // int second_letter = 0;
    // int third_letter = 0;
    // int fourth_letter = 0;
    // int fifth_letter = 0;
    // // We check the first & second letter, We find the value of it
    // if(word[41 ] != '\0')
    // {
    //     first_letter = toupper(word[0]) - 'A';
    //     second_letter = toupper(word[1]) - 'A';
    //     third_letter = toupper(word[2]) - 'A';
    //     fourth_letter = toupper(word[3]) - 'A';
    //     fifth_letter = toupper(word[4]) - 'A';
    //     hash_value = ((26 * first_letter) + (26 * second_letter) + (26 * third_letter) + (26 * fourth_letter) + fifth_letter);
    // }
    // if(word[3] != '\0')
    // {
    //     first_letter = toupper(word[0]) - 'A';
    //     second_letter = toupper(word[1]) - 'A';
    //     third_letter = toupper(word[2]) - 'A';
    //     fourth_letter = toupper(word[3]) - 'A';
    //     hash_value = ((26 * first_letter) + (26 * second_letter) + (26 * third_letter) + fourth_letter);
    // }
    // if(word[2] != '\0')
    // {
    //     first_letter = toupper(word[0]) - 'A';
    //     second_letter = toupper(word[1]) - 'A';
    //     third_letter = toupper(word[2]) - 'A';
    //     hash_value = ((26 * first_letter) + (26 * second_letter) + third_letter);
    // }
    // if(word[1] != '\0')
    // {
    //     first_letter = toupper(word[0]) - 'A';
    //     second_letter = toupper(word[1]) - 'A';
    //     hash_value = ((26 * first_letter) + second_letter);
    // }
    // else
    // {
    //     first_letter = toupper(word[0]) - 'A';
    //     hash_value = first_letter;
    // }
    // // For firstletter = 0. secondletter = 2, (firstletter + secondletter)
    // // For firstletter = 3, secondletter = 3, (26 * firstletter + secondletter)

    // // Second Approach: Rolling Polynomial Hash Function
    int i = 0;
    int base = 3;
    int hash_value = 0;
    for (i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            int letter_value = toupper(word[i]) - 'A';
            // Create a hash value with a formula
            hash_value = hash_value * base + letter_value;
            // check if there's another letter
            // add that value to the hash value
            // printf("%c", word[i]);
        }
        else if (word[i] == '\'')
        {
            break;
        }
    }
    // TODO: Improve this hash function
    // printf(" %i\n ", hash_value);
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    // // Check if the file opened, if not close the prorgram with error
    if (source == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }
    char new_word[46];
    // Read each word in the file
    while(fscanf(source, "%s", new_word) != EOF)
    {
        // Add each word to the hash table
        // // Create space for a new hash table node
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
        printf("Unable to assign memory for node\n");
        return false;
        }
        // // Copy the word into the new node
        strcpy(new_node->word, new_word);
        new_node->next = NULL;
        // // Hash the word to obtain its hash value
        int hash_value = hash(new_word);
        // // Insert the new node into the hash table(using the index specified by its hash value)
        // // // Assign the current word next value to the pointer from the start of the list
        new_node->next = table[hash_value];
        // // // Assign the start pointer to the current word
        table[hash_value] = new_node;
    }

    // Close the dictionary file
    fclose(source);

    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Go through the Hash Table and Count each Linked List
    int n = 0;
    int numofwords = 0;
    for (n = 0; (n < 500000); n++)
    {
        node *cursor = table[n];
        while(cursor != NULL)
        {
            numofwords++;
            cursor = cursor->next;
        }
    }
    return numofwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Make a temp node to assign the cursor value
    // Move the cursor to the next node
    // Clear the memeory for the temp node
    // If cursor find NULL, end the loop
    for (int n = 0; (n < 500000); n++)
    {
        node *cursor = table[n];
        while(cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free (tmp);
        }
    }
    // TODO
    return true;
}
