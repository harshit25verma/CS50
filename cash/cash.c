#include <stdio.h>
#include <cs50.h>

int main(void)
{
 //Get the amount from the User b/w 1-100
    int amount;
    do
    {
        amount = get_int("Change owed: ");
    }
    while(amount<0);

//Divide the amount first with 25
int quarters = amount/25;
//Multiply 25 with number of coins
int remaining_Q = amount - (quarters*25);

//Divide the amount second with 10
int tens = remaining_Q/10;
//Multiply  with number of coins
int remaining_T = remaining_Q - (tens*10);

//Divide the amount third with 5
int fives = remaining_T/5;
//Multiply  with number of coins
int remaining_F = remaining_T - (fives*5);

//Divide the amount fourht with 1
int ones = remaining_F/1;

//Add the the number of coins
int sum = quarters+tens+fives+ones ;
//Show the number of coins
printf("Total Coins:%i\n", sum);

}
