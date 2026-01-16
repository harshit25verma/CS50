#include <stdio.h>
#include <cs50.h>


void print_spaces(int rows, int height);
void print_rows( int rows);

int main(void)
{
    int height;

    do
    {
    height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Print the no. of rows
    for (int rows = 1; rows <= height; rows++)
    {

    //Print the no. of spaces
        print_spaces(rows, height);

    //Print the no. of items in a row
        print_rows(rows);

    printf("\n");

    }
}




void print_spaces(int rows, int height)
{
    //Print the no. of spaces
    for (int spaces = 0; spaces < (height-rows); spaces++)
    {
        printf(" ");
    }
}

void print_rows(int rows)
{
    for (int bricks = 0; bricks < rows; bricks++)
    {
        printf("#");
    }
}
