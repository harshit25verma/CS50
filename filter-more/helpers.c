#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // move to the 0 row of the array
    {
        for (int j = 0; j < width; j++) // move to the 0 column of the array
        {
            // check and change the value of the current pixel of the image array
            float grayscaleValue =
                round((float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) /
                      3); // add the R + G + B and divide by three
            image[i][j].rgbtBlue = grayscaleValue;
            image[i][j].rgbtGreen = grayscaleValue;
            image[i][j].rgbtRed = grayscaleValue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int reflectUntil;
    if (round(width /
              2)) // if the pixels in the width are even, then run this (if width/2 = round number)
    {
        reflectUntil = width / 2; // change the values until width/2 pixel
    }
    else // if the pixels in the width are odd, run this (if width/2 = not a round number)
    {
        reflectUntil = (width - 1) / 2; // chnage the values until (width-1)/2 pixel
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < reflectUntil; j++)
        {
            // check and change the value of the current pixel to the other pixel on the same
            // posiition
            RGBTRIPLE buffer; // make a buffer value of type RGBTRIPLE declared in bmp.h to store
                              // RGB values temporarily
            int reflectValue = (width - j - 1); // reflectValue is the value need to swapped with (width
                                            // - j value) SWAPPING For Blue Value of the pixel
            buffer.rgbtBlue = image[i][reflectValue].rgbtBlue; // assign the reflectValue pixel value to the buffer temprarily
            image[i][reflectValue].rgbtBlue = image[i][j].rgbtBlue; // assign the normal number pixel value to the refelctValue pixel
            image[i][j].rgbtBlue = buffer.rgbtBlue; // assign the buffer value, which is the
                                                    // refelctValue stored earlier, to the normal
            // pixel value For Green Value of the pixel
            buffer.rgbtGreen = image[i][reflectValue].rgbtGreen;
            image[i][reflectValue].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = buffer.rgbtGreen;
            // For Red Value of the pixel
            buffer.rgbtRed = image[i][reflectValue].rgbtRed;
            image[i][reflectValue].rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = buffer.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // go to the pixel
    // add all the values of RED for example, of all the pixels around it
    // .______________________________.
    // |(i-1, j-1)|(i-1, j)|(i-1, j+1)|
    // |__________|________|__________|
    // | (i, j-1) | (i, j) | (i, j+1) |
    // |__________|________|__________|
    // |(i+1, j-1)|(i+1, j)|(i+1, j+1)|
    // |__________|________|__________|
    //
    // .______________________________.
    // |    (1)   |   (2)  |    (3)   |
    // |__________|________|__________|
    // |    (4)   | (i, j) |    (5)   |
    // |__________|________|__________|
    // |    (6)   |   (7)  |    (8)   |
    // |__________|________|__________|
    // Basically we can change the number to an operator since the swtich is between -1, 0, 1, and
    // create placeholder h, k, in the equation (i-h), (j-k)
    // so somehting like, image[i-h][j-k].rgbtRed
    // for (float h = -1, h <= 1, h++)
    // for (float k = -1, k <= 1, k++)
    // SumValue =+ image[i + h][j + k].rgbtRed
    // Now we can check if the image[i + h][j + k].rgbtRed is not NULL/Empty, if it is, we chnage
    // it's vlaue to zero and remove 1 from the 8 pixels, lets take an int PixelsLeft = 8, and
    // eventually keeps getting -1 as we get a NUll value from a pixel

    //declare a buffer
    RGBTRIPLE buffer[height][width];

    // Move to Each Pixel
    for (int i = 0; i < height; i++) // move to the row
    {
        for (int j = 0; j < width; j++) // move to the column
        {
            int SumValueRed = 0;
            int SumValueGreen = 0;
            int SumValueBlue = 0;
            int PixelsLeft = 9; // Declare number of pixels to be averaged by

            // Record values around that Pixel
            for (int h = -1; h <= 1; h++) // chnage row value for the pixels around
            {
                for (int k = -1; k <= 1; k++) // change column value for the pixels around
                {
                    if ((0 <= (i + h) && (i + h) < height && 0 <= (j + k) && (j + k) < width)) // We check if the value is either less, than 0 or more than width or height
                    {
                        SumValueRed += image[i + h][j + k].rgbtRed; // Keep adding the value of the Pixels color into SumValue
                        SumValueGreen += image[i + h][j + k].rgbtGreen; // Keep adding the value of the Pixels color into SumValue
                        SumValueBlue += image[i + h][j + k].rgbtBlue; // Keep adding the value of the Pixels color into SumValue
                    }
                    else // If the value calculated is NULL/Empty
                    {
                        // SumValueRed += 0; // We add only 0 to the Sum Value
                        PixelsLeft -= 1; // We decrease the Pixels to be averaged by 1
                    }
                }
            }
            buffer[i][j].rgbtRed = round(round(SumValueRed) / PixelsLeft); // Assign the Averaged value to the Pixel
            buffer[i][j].rgbtGreen = round(round(SumValueGreen) / PixelsLeft); // Assign the Averaged value to the Pixel
            buffer[i][j].rgbtBlue = round(round(SumValueBlue) / PixelsLeft); // Assign the Averaged value to the Pixel
        }
    }

    // Copy the buffer to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }
    // return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Some Theory
    // We need to apply two convolution matrix
    // .___________________.
    // | (-1) | (0) | (1) |
    // |______|_____|_____|
    // | (-2) | (0) | (2) |
    // |______|_____|_____|
    // | (-1) | (0) | (1) |
    // |______|_____|_____|
    //  Gx
    // .____________________.
    // | (-1) | (-2) | (-1) |
    // |______|______|______|
    // |  (0) |  (0) |  (0) |
    // |______|______|______|
    // |  (1) |  (2) |  (1) |
    // |______|______|______|
    //  Gy
    //
    // .______________________________.
    // |(i-1, j-1)|(i-1, j)|(i-1, j+1)|
    // |__________|________|__________|
    // | (i, j-1) | (i, j) | (i, j+1) |
    // |__________|________|__________|
    // |(i+1, j-1)|(i+1, j)|(i+1, j+1)|
    // |__________|________|__________|
    //
    // Matrix will work as follows:
    // Gx = (-1)*(i-1)+(0)*(i-1)+(1)*(i-1)+(-2)*(i)+(0)*(i)+(2)*(i)+(-1)*(i+1)+(0)*(i+1)+(1)*(i+1)
    // Gy = (-1)*(j-1)+(-2)*(j)+(-1)*(j+1)+(0)*(j-1)+(0)*(j)+(0)*(j+1)+(1)*(j-1)+(2)*(j)+(1)*(j+1)
    //
    // image[i][j].rgbtRed

    RGBTRIPLE buffer[height][width]; // Declaring a buffer value

    // Move to the Pixel on the Image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Decalring Gx and Gy
            int GxRed = 0;
            int GyRed = 0;
            int GxGreen = 0;
            int GyGreen = 0;
            int GxBlue = 0;
            int GyBlue = 0;

            // Declaring Red, Green, Blue
            int Red = 0;
            int Green = 0;
            int Blue = 0;

            // Assigning the

            //  printf("before loop %i %i %i\n", GxRed, GxBlue, GxGreen);
            // If loop for -1
            if (((i - 1) < 0) || ((i - 1) >= height) || ((j - 1) < 0) || ((j - 1) >= width))
            {
                //  printf("Out of Bound 1\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                //  printf(" %i %i %i\n", GxRed, GxBlue, GxGreen);
                GxRed += (-1) * (image[i - 1][j - 1].rgbtRed);
                GxBlue += (-1) * (image[i - 1][j - 1].rgbtBlue);
                GxGreen += (-1) * (image[i - 1][j - 1].rgbtGreen);

                GyRed += (-1) * (image[i - 1][j - 1].rgbtRed);
                GyBlue += (-1) * (image[i - 1][j - 1].rgbtBlue);
                GyGreen += (-1) * (image[i - 1][j - 1].rgbtGreen);

                //  printf(" %i %i %i\n", GxRed, GxBlue, GxGreen);
                //  printf(" %i %i %i\n", GyRed, GyBlue, GyGreen);
            }

            // if loop for -2
            if (((j - 1) < 0))
            {
                //  printf("Out of Bound 2\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (-2) * (image[i][j - 1].rgbtRed);
                GxBlue += (-2) * (image[i][j - 1].rgbtBlue);
                GxGreen += (-2) * (image[i][j - 1].rgbtGreen);

                GyRed += (0) * (image[i][j - 1].rgbtRed);
                GyBlue += (0) * (image[i][j - 1].rgbtBlue);
                GyGreen += (0) * (image[i][j - 1].rgbtGreen);
            }

            // if loop for -1
            if (((i + 1) < 0) || ((i + 1) >= height) || ((j - 1) < 0) || ((j - 1) >= width))
            {
                //  printf("Out of Bound 3\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (-1) * (image[i + 1][j - 1].rgbtRed);
                GxBlue += (-1) * (image[i + 1][j - 1].rgbtBlue);
                GxGreen += (-1) * (image[i + 1][j - 1].rgbtGreen);

                GyRed += (1) * (image[i + 1][j - 1].rgbtRed);
                GyBlue += (1) * (image[i + 1][j - 1].rgbtBlue);
                GyGreen += (1) * (image[i + 1][j - 1].rgbtGreen);
            }

            // if loop for 0
            if (((i - 1) < 0) || ((i - 1) >= height))
            {
                //  printf("Out of Bound 4\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (0) * (image[i - 1][j].rgbtRed);
                GxBlue += (0) * (image[i - 1][j].rgbtBlue);
                GxGreen += (0) * (image[i - 1][j].rgbtGreen);

                GyRed += (-2) * (image[i - 1][j].rgbtRed);
                GyBlue += (-2) * (image[i - 1][j].rgbtBlue);
                GyGreen += (-2) * (image[i - 1][j].rgbtGreen);
            }

            // if loop for 0
            if (((i) < 0) || ((i) >= height) || ((j) < 0) || ((j) >= width))
            {
                //  printf("Out of Bound 5\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (0) * (image[i][j].rgbtRed);
                GxBlue += (0) * (image[i][j].rgbtBlue);
                GxGreen += (0) * (image[i][j].rgbtGreen);

                GyRed += (0) * (image[i][j].rgbtRed);
                GyBlue += (0) * (image[i][j].rgbtBlue);
                GyGreen += (0) * (image[i][j].rgbtGreen);
            }

            // if loop for 0
            if (((i + 1) < 0) || ((i + 1) >= height))
            {
                //  printf("Out of Bound 6\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (0) * (image[i + 1][j].rgbtRed);
                GxBlue += (0) * (image[i + 1][j].rgbtBlue);
                GxGreen += (0) * (image[i + 1][j].rgbtGreen);

                GyRed += (2) * (image[i + 1][j].rgbtRed);
                GyBlue += (2) * (image[i + 1][j].rgbtBlue);
                GyGreen += (2) * (image[i + 1][j].rgbtGreen);
            }

            // if loop for 1
            if (((i - 1) < 0) || ((i - 1) >= height) || ((j + 1) < 0) || ((j + 1) >= width))
            {
                //  printf("Out of Bound 7\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (1) * (image[i - 1][j + 1].rgbtRed);
                GxBlue += (1) * (image[i - 1][j + 1].rgbtBlue);
                GxGreen += (1) * (image[i - 1][j + 1].rgbtGreen);

                GyRed += (-1) * (image[i - 1][j + 1].rgbtRed);
                GyBlue += (-1) * (image[i - 1][j + 1].rgbtBlue);
                GyGreen += (-1) * (image[i - 1][j + 1].rgbtGreen);
            }

            // if loop  for 2
            if (((i) < 0) || ((i) >= height) || ((j + 1) < 0) || ((j + 1) >= width))
            {
                //  printf("Out of Bound 8\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (2) * (image[i][j + 1].rgbtRed);
                GxBlue += (2) * (image[i][j + 1].rgbtBlue);
                GxGreen += (2) * (image[i][j + 1].rgbtGreen);

                GyRed += (0) * (image[i][j + 1].rgbtRed);
                GyBlue += (0) * (image[i][j + 1].rgbtBlue);
                GyGreen += (0) * (image[i][j + 1].rgbtGreen);
            }

            // if loop for 1
            if (((i + 1) < 0) || ((i + 1) >= height) || ((j + 1) < 0) || ((j + 1) >= width))
            {
                //  printf("Out of Bound 9\n");
                GxRed += 0;
                GxBlue += 0;
                GxGreen += 0;

                GyRed += 0;
                GyBlue += 0;
                GyGreen += 0;
            }
            else
            {
                GxRed += (1) * (image[i + 1][j + 1].rgbtRed);
                GxBlue += (1) * (image[i + 1][j + 1].rgbtBlue);
                GxGreen += (1) * (image[i + 1][j + 1].rgbtGreen);

                GyRed += (1) * (image[i + 1][j + 1].rgbtRed);
                GyBlue += (1) * (image[i + 1][j + 1].rgbtBlue);
                GyGreen += (1) * (image[i + 1][j + 1].rgbtGreen);
            }

            // Assign combined value of convulation matrix colours
            Red = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
            Green = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));
            Blue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));

            // Make a buffer image
            // Red Compilation of the Convolution Matrix
            // printf("Red: ");
            if (Red > 255)
            {
                // printf("255 ");
                buffer[i][j].rgbtRed = 255;
            }
            else if (Red < 0)
            {
                // printf("0 ");
                buffer[i][j].rgbtRed = 0;
            }
            else
            {
                buffer[i][j].rgbtRed = Red;
                // printf("%i", buffer[i][j].rgbtRed);
            }

            // Green Compilation of the Convolution Matrix
            //  printf(" Green: ");
            if (Green > 255)
            {
                // printf("255 ");
                buffer[i][j].rgbtGreen = 255;
            }
            else if (Green < 0)
            {
                // printf("0 ");
                buffer[i][j].rgbtGreen = 0;
            }
            else
            {
                buffer[i][j].rgbtGreen = Green;
                // printf("%i ", buffer[i][j].rgbtGreen);
            }

            // Blue Compilation of the Convolution Matrix
            //  printf(" Blue: ");
            if (Blue > 255)
            {
                // printf("255 \n");
                buffer[i][j].rgbtBlue = 255;
            }
            else if (Blue < 0)
            {
                // printf("0 \n");
                buffer[i][j].rgbtBlue = 0;
            }
            else
            {
                buffer[i][j].rgbtBlue = Blue;
                // printf("%i\n", buffer[i][j].rgbtBlue);
            }
        }
    }

    // Copy the buffer image to the main image to be able to be shown through main code
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = buffer[i][j].rgbtBlue;
        }
    }

    // return;
}
