#include <stdio.h>
#include <cs50.h>

void print_spaces(int height, int rows);
void print_bricks(int rows);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while(height<1 || height>8);

    int rows;
    for (rows = 1; rows <= height; rows++)
    {
        //Print decreasing Spaces
            print_spaces(height, rows);
        //Print Increasing Bricks
            print_bricks(rows);

        //Print the gap between
        printf("  ");

        //Print Increasing Bricks
            print_bricks(rows);

        printf("\n");
    }
}





//Print decreasing Spaces
void print_spaces(int height, int rows)
{
    for (int spaces = 0; spaces < (height - rows); spaces++)
    {
        printf(" ");
    }
}

//Print Increasing Bricks
void print_bricks(int rows)
{
    for(int bricks = 0; bricks < rows; bricks++)
    {
        printf("#");
    }
}
