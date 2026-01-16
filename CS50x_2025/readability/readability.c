#include <stdio.h> //Standard Library included
#include <cs50.h> //CS50 Library included
#include <ctype.h> //ctype Library included
#include <math.h>

int main (void)
{
    //GET USER INPUT
    string input_text; //declaration of string input_text outside the loop to let it be called out by other functions/loops
    do
    {
    input_text = get_string("Text: "); //Get the input using the CS50 get_string
    }
    while (input_text[0] == '\0' || isspace(input_text[0])); //Keep asking for the input_text until the first alpahbet is a null (\0) or a space

    //COUNT THE NUMBER OF WORDS, LETTER AND SENTENCES
    int n = 0;
    float word = 1; //Since we are checking spaces between words, there is always going to be one space missing before the first word, We count that soace as one word
    float sentence = 0;
    float letter = 0;
    while (input_text[n] != '\0' ) //While n is the nth element of array we are checking of the string, starting from 0
    {
        if (isspace(input_text[n])) //Check if there is a space
        {
        word++; //If there a space, +1 word count
        }
        else if (input_text[n] == '.' || input_text[n] == '!' || input_text[n] == '?') //Check if there is a punctuation
        {
        sentence++; //If there a puntuation, +1 sentence count
        }
        else if (isalnum(input_text[n])) //Check if there is a alphabet or number
        {
        letter++; //If there a alphabet or number, +1 letter count
        }
    n++; //Increase the nth value by +1
    }
    // printf ("Words: %i \n", word);
    // printf ("Sentences: %i \n", sentence);
    // printf ("Letters: %i \n", letter);

    //CALCULATE THE COLEMAN-LIAU INDEX
    float L = (letter/word) * 100;
    float S = (sentence/word) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //PRINT THE GRADE
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
    printf("Grade %i\n",(int) round(index));
    //where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    }
}


// //Get Text prompt from the User
// string User_Input()
// {
//     do
//     {
//         string text = get_string("Text: ");     //get prompt from the User
//         //n++;
//     }
//     while (isblank(text[n]) || isdigit(text[n]) || isspace(text[n]));
//     return text;
// }




