#include <stdio.h>
#include <cs50.h>

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int h = -1; h <= 1; h++) // chnage row value for the pixels around
            {
                for (int k = -1; k <= 1; k++) // change column value for the pixels around
                {
                    printf("%i", i);
                    printf(" + %i   ", h);
                    printf("%i", j);
                    printf(" + %i   ", k);
                }
                printf("\n");
            }
        }
    }
}
