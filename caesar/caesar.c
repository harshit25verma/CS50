#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

string encryption(string argv[]);
int keymaking(string argv[1]);
string plaintext();
int cipher(string plaintext);
char text[] = {};                               //an empty array text to store any characters
char UpperAlphabets[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char LowerAlphabets[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main (int argc, string argv[])
{
    //This loop check each character for a alphabet, if atleast one alphabet is detected, or if the number of arguments in commad line is less or more than 2
    int n = 0;
    int errors = 0;
    if(argc != 2)
    {
        errors++;                                           //add en error
    }
    else if(argc >= 2)
    {
        while(argv[1][n] != '\0')
        {
            //If the situation is true, make something TRUE/FALSE and if atleast one of them is FALSE, return 'IS NOT DIGIT'(temp)
            if((isalpha(argv[1][n])))  //if number of arguments are not 2 OR if the argument's second [1] element each element [n] is an alphabet
            {
                errors++;                               //add en error
            }
            //If the situation is true, make something TRUE/FALSE and if atleast one of them is FALSE, return 'IS DIGIT'(temp)
            else if(isdigit(argv[1][n]))            //if the argument's second [1] element 's each element [n] is a digit
            {
            }
        n++;
        }
    }

    //This loop executes the functions that actually execute the primary functions, what was the outout from the previous loop
    if(errors >> 0)                         //If errors variable is more than 0
    {
        printf("Usage: ./ceasar key\n");    //error message printed when error is generated at the input on command line
        return 1;                           //Return a value of 1 to main, to register error
    }
    else if(errors == 0)                    //If errors variable is 0
    {
        encryption(argv);                           //Run the Encryption function
        printf("ciphertext: %s\n", text);           //Print the Ciphertext with the converted text from the text variable
        return 0;                                   //Return a value of 0 to main, to register everything's ok
    }
}










//ENCRYPT THE TEXT INTO A CIPHER
string encryption(string argv[])
{
        //Process the User Input plaintext
        int c = 0;
        string P = plaintext();             //Call out the plaintext function and store it in a variable P to be used in future
        int key = keymaking(argv);          //Call out the keymaking function and store it in a variable key to be used in future
        while(P[c] != '\0')                 //take the plaintext and move to each element of the string array on by one
        {
            //GEENRATE THE CIPHERTEXT BY APPLYING THE EQUATION
            if (isalpha(P[c]))                     //If plaintext is an alphabet, checked by isalpha functiion
            {
                if(isupper(P[c]))                               //check if the letter is uppercase
                {
                //change the value by adding the key and applying the formaula to always get a fallback after 26
                    int value = ((P[c] - 65) + key) % 26 ;       //assign the value to an int value for uppercase letter
                    text[c] = UpperAlphabets[value];             //chose from the alphabets array with the int and assign to the empty array value
                }
                else if(islower(P[c]))                           //check if the letter is lowercase
                {
                    int value = ((P[c] - 97) + key) % 26 ;       //assign the value to an int value for lowercase letter
                    text[c] = LowerAlphabets[value];             //chose from the alphabets array with the int and assign to the empty array value
                }
            }
            else
            {
                text[c] = P[c];                     //if it is not a an alpabet, don't chnage anything, store in the text array
            }
            c++;
        }
        return text;
}






//MAKE THE KEY
int keymaking(string argv[1])
{
    //convert the string to int
    int keyvalue = atoi(argv[1]);            //change the string into an int value using the atoi function from the stblib.h and store in a variable keyvalue
    return keyvalue;                         //return the function keyvalue to be reused throughout the code
}







//TAKE THE USER INPUT AS PLAINTEXT
string plaintext()
{
    //Get User Input
    string pt = get_string("plaintext: ");   //get the user input using the get_string and store it in a variable pt
    return pt;                               //return the function pt to be reused throughout the code
}
