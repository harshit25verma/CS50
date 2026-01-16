#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Usage to the User
    if (argc !=2)
    {
        printf("Usage: ./recover card.raw");
    }

    // Create a buffer of 512 bytes
    uint8_t buffer[512];

    // Create a Signature
    uint8_t signature[3] = {0xff, 0xd8, 0xff};

    // Decalre the file
    char image[9] = {};

    // Open the memory card
    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = NULL; //Declaring the output file globally to be used later

    int CurrentImage = 0; //Assign a  value to a variable

    // Check if the Signature and Buffer match
    while (fread(buffer, 512, 1, input)) //While blocks in input are not empty, read input into buffer 512 bytes each time
    {
        // If the Start of the image, run this loop
        if (buffer[0] == signature[0] && buffer[1] == signature[1] && buffer[2] == signature[2]) // //If the three match, Image file starts //Run a loop if the value start of the image
        {
            if (output != NULL) // If the output file is not NULL, we can close it before opening new one, if it is null, we ignore and move on
            {
                fclose(output); //close the output file
            }
            sprintf(image, "%03i.jpg", CurrentImage); //Rename the file into bit sixe of image array to store the name there
            // Write the image
            output = fopen(image, "w"); // Make new file image to be written
            if (output == NULL)
            {
                printf("Could not open output file.\n"); //Just a check and safety measure if file not being able to open
                return 1; //will close the main function instantly
            }
            fwrite(buffer, 512, 1, output); //Start wrtiing into the buffer file
            // Increase the value if the start of an image
            CurrentImage++;
        }
        // If the CurrentImage > 0 and not the start of an image
        else if (CurrentImage > 0 && !(buffer[0] == signature[0] && buffer[1] == signature[1] && buffer[2] == signature[2])) // Let's write a image until we find another image
        {
            fwrite(buffer, 512, 1, output); // Start wrtiing into the buffer file/ /If not the start of the image, keep writing
        }
    }
    fclose(input); //Close input file
    fclose(output); //Close output file
}
