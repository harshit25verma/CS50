#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
//              A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W,  X, Y, Z
int Points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int Scoreboard[] = {};

long Convert(string word);
void compare_score (int Score);

int main (void)
{
    string word;
    int Score;
    int n = 0;

      for(int player = 1; player <= 2; player++)
      {
        do
        {
        word = get_string("Player %i: ", player);
        }
        while (isblank(word[n]) || isdigit(word[n]) || isspace(word[n]));

        Score = Convert(word);
        Scoreboard[player] = Score;
      }
      compare_score(Score);
}







//compare player_one and player_two
void compare_score (int Score)
{
  if (Scoreboard[1] > Scoreboard[2])
  {
    printf("Player 1 wins!\n");     //if player_one > player_two, print Player 1 wins!
  }
    else if (Scoreboard[1] < Scoreboard[2])
    {
          printf("Player 2 wins!\n");     //if player_two < player_one, print Player 2 wins!
    }
      else if (Scoreboard[1] == Scoreboard[2])
      {
            printf("Tie!\n");     //if player_one = player_two, Tie!
      }

}









long Convert(string word)
  {
   //run a loop to go to the character of a string
   int n = 0;
   int Score = 0;
   int Alphabet;
   int UppAlphabet;
   while (word[n] != '\0')    //repeat until '\0'(null) found
   {
   //If it is a alphabet
    if (isalpha(word[n]))
    {
        //If Lowercase, then impment this function
        if (islower(word[n]))
        {
            Alphabet = (word[n] - 97); //change char to an int value for scrabble rules
        }
        //Else if Uppercase, implement this function
        else if (isupper(word[n]))
        {
            Alphabet = (word[n] - 65); //change char to an int value for scrabble rules
        }
    }
    //else, break the og if/else loop and go out to implement next steps
    else
    {
      break;
    }

      Score += Points[Alphabet]; //Score is equal to the Points of LowAlphabet value and added at each iteration(add them one by one)

      n++;    //go to the next character

   }

     // printf("%i\n", Score);
      return Score;

  }




