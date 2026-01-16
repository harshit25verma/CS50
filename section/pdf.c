#include <stdio.h>
#include <cs50.h>
#include <stdint.h>

int main (int argc, string argv[])
{
    // Check Usage for CLA
    if (argc != 2)
    {
        printf("Usage: ./pdf filename\n");
        return 1;
    }

    // Open file
    FILE *input = fopen(argv[1], "r");

    // Create buffer for file
    uint8_t buffer[4];

    // Create an array of signature bytes
    uint8_t signature[] = {0x25, 0x50, 0x44, 0x46};

    // Ready first 4 bytes from the file
    fread(buffer, sizeof(uint8_t), 4, input);

    // Check the first 4 bytes against signature bytes
    for (int i = 0; i < 4; i++)
    {
        if(signature[i] != buffer[i])
        {
            printf("This is not a pdf\n");
        }
        else if (signature[i] != buffer[i])
        {
            printf("Success");
        }
    }

    // Success!
}
