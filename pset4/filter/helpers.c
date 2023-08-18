#include <stdio.h>
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //Makes the sum of all values e takes the rounded average
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            image[i][j].rgbtBlue = sum / 3 + 0.5;
            image[i][j].rgbtGreen = sum / 3 + 0.5;
            image[i][j].rgbtRed = sum / 3 + 0.5;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        //ignores 1px wide images
        if (width != 1)
        {

            //for images with even width
            if ((width % 2) == 0)
            {
                for (int j = 0; j < width / 2; j++)
                {
                    RGBTRIPLE temp = image[i][j];
                    image[i][j] = image[i][width - (j + 1)];
                    image[i][width - (j + 1)] = temp;

                }
            }


            //for images with odd width, ignores the middle column
            else
            {
                for (int j = 0; j < round(width / 2); j++)
                {
                    RGBTRIPLE temp = image[i][j];
                    image[i][j] = image[i][width - (j + 1)];
                    image[i][width - (j + 1)] = temp;

                }
            }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    for (int i = 0; i <= (height - 1); i++)
    {
        for (int j = 0; j <= (width - 1); j++)
        {
            float red = 0;
            float green = 0;
            float blue = 0;
            int runs = 0;

            //TOP
            if (i == 0)
            {
                //LEFT TOP CORNER
                if (j == 0)
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = 0; y <= 1; y++)
                        {
                            blue += image[(i + x)][(j + y)].rgbtBlue;
                            red += image[(i + x)][(j + y)].rgbtRed;
                            green += image[(i + x)][(j + y)].rgbtGreen;
                            runs++;
                        }
                    }
                }

                //RIGHT TOP CORNER
                else if (j == (width - 1))
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 0; y++)
                        {
                            blue += image[(i + x)][(j + y)].rgbtBlue;
                            red += image[(i + x)][(j + y)].rgbtRed;
                            green += image[(i + x)][(j + y)].rgbtGreen;
                            runs++;
                        }
                    }
                }

                else
                {
                    //TOP EDGE
                    for (int x = 0; x <= 1; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 1; y++)
                        {
                            blue += image[(i + x)][(j + y)].rgbtBlue;
                            red += image[(i + x)][(j + y)].rgbtRed;
                            green += image[(i + x)][(j + y)].rgbtGreen;
                            runs++;
                        }
                    }
                }
            }

            //BOTTOM
            if (i == (height - 1))
            {
                //LEFT BOTTOM CORNER
                if (j == 0)
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = 0; y <= 1; y++)
                        {
                            blue += image[(i + x)][(j + y)].rgbtBlue;
                            red += image[(i + x)][(j + y)].rgbtRed;
                            green += image[(i + x)][(j + y)].rgbtGreen;
                            runs++;
                        }
                    }
                }

                //RIGHT BOTTOM CORNER
                else if (j == (width - 1))
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 0; y++)
                        {
                            blue += image[(i + x)][(j + y)].rgbtBlue;
                            red += image[(i + x)][(j + y)].rgbtRed;
                            green += image[(i + x)][(j + y)].rgbtGreen;
                            runs++;
                        }
                    }
                }

                else
                {
                    //BOTTOM EDGE
                    for (int x = -1; x <= 0; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 1; y++)
                        {
                            blue += image[(i + x)][(j + y)].rgbtBlue;
                            red += image[(i + x)][(j + y)].rgbtRed;
                            green += image[(i + x)][(j + y)].rgbtGreen;
                            runs++;
                        }
                    }
                }
            }

            else if ((j == 0) && ((i > 0) && (i < height - 1)))
            {
                //LEFT EDGE
                for (int x = -1; x <= 1; x++)
                {
                    //SUM ALL PIXELS IN THE BOX
                    for (int y = 0; y <= 1; y++)
                    {
                        blue += image[(i + x)][(j + y)].rgbtBlue;
                        red += image[(i + x)][(j + y)].rgbtRed;
                        green += image[(i + x)][(j + y)].rgbtGreen;
                        runs++;
                    }
                }
            }

            else if ((j == width - 1) && ((i > 0) && (i < height - 1)))
            {
                //RIGTH EDGE
                for (int x = -1; x <= 1; x++)
                {
                    //SUM ALL PIXELS IN THE BOX
                    for (int y = -1; y <= 0; y++)
                    {
                        blue += image[(i + x)][(j + y)].rgbtBlue;
                        red += image[(i + x)][(j + y)].rgbtRed;
                        green += image[(i + x)][(j + y)].rgbtGreen;
                        runs++;
                    }
                }
            }


            //HANDLES MIDLE OF IMAGE
            else if ((i > 0) && (j > 0) && (i < (height - 1)) && (j < (width - 1)))
            {
                for (int x = -1; x <= 1; x++)
                {
                    //SUM ALL PIXELS IN THE BOX
                    for (int y = -1; y <= 1; y++)
                    {
                        blue += image[(i + x)][(j + y)].rgbtBlue;
                        red += image[(i + x)][(j + y)].rgbtRed;
                        green += image[(i + x)][(j + y)].rgbtGreen;
                        runs++;
                    }
                }
            }

            //MAKES THE AVERAGE AND ROUND THEM
            blue = blue / runs + 0.5;
            red =  red / runs + 0.5;
            green = green  / runs + 0.5;

            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    for (int i = 0; i < (height); i++)
    {
        for (int j = 0; j < (width); j++)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;

            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            //TOP
            if (i == 0)
            {
                //LEFT TOP CORNER
                if (j == 0)
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = 0; y <= 1; y++)
                        {
                            blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                            redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                            greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                            blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                            redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                            greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                        }
                    }
                }

                //RIGHT TOP CORNER
                else if (j == (width - 1))
                {
                    for (int x = 0; x <= 1; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 0; y++)
                        {
                            blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                            redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                            greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                            blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                            redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                            greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                        }
                    }
                }

                else
                {
                    //TOP EDGE
                    for (int x = 0; x <= 1; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 1; y++)
                        {
                            blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                            redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                            greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                            blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                            redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                            greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                        }
                    }
                }
            }

            //BOTTOM
            else if (i == (height - 1))
            {
                //LEFT BOTTOM CORNER
                if (j == 0)
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = 0; y <= 1; y++)
                        {
                            blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                            redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                            greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                            blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                            redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                            greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                        }
                    }
                }

                //RIGHT BOTTOM CORNER
                else if (j == (width - 1))
                {
                    for (int x = -1; x <= 0; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 0; y++)
                        {
                            blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                            redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                            greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                            blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                            redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                            greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                        }
                    }
                }

                else
                {
                    //BOTTOM EDGE
                    for (int x = -1; x <= 0; x++)
                    {
                        //SUM ALL PIXELS IN THE BOX
                        for (int y = -1; y <= 1; y++)
                        {
                            blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                            redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                            greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                            blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                            redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                            greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                        }
                    }
                }
            }

            //LEFT
            else if ((j == 0) && ((i > 0) && (i < height - 1)))
            {
                //LEFT EDGE
                for (int x = -1; x <= 1; x++)
                {
                    //SUM ALL PIXELS IN THE BOX
                    for (int y = 0; y <= 1; y++)
                    {
                        blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                        redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                        greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                        blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                        redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                        greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                    }
                }
            }

            //RIGHT
            else if ((j == width - 1) && ((i > 0) && (i < height - 1)))
            {
                //RIGTH EDGE
                for (int x = -1; x <= 1; x++)
                {
                    //SUM ALL PIXELS IN THE BOX
                    for (int y = -1; y <= 0; y++)
                    {
                        blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                        redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                        greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                        blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                        redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                        greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                    }
                }
            }

            //HANDLES MIDLE OF IMAGE
            else if ((i > 0) && (j > 0) && (i < (height - 1)) && (j < (width - 1)))
            {
                for (int x = -1; x <= 1; x++)
                {
                    //SUM ALL PIXELS IN THE BOX
                    for (int y = -1; y <= 1; y++)
                    {
                        blueX += (image[(i + x)][(j + y)].rgbtBlue * Gx[x + 1][y + 1]);
                        redX += (image[(i + x)][(j + y)].rgbtRed * Gx[x + 1][y + 1]);
                        greenX += (image[(i + x)][(j + y)].rgbtGreen * Gx[x + 1][y + 1]);

                        blueY += (image[(i + x)][(j + y)].rgbtBlue * Gy[x + 1][y + 1]);
                        redY += (image[(i + x)][(j + y)].rgbtRed * Gy[x + 1][y + 1]);
                        greenY += (image[(i + x)][(j + y)].rgbtGreen * Gy[x + 1][y + 1]);
                    }
                }
            }


            int B = round(sqrt(pow(blueX, 2) + pow(blueY, 2)));
            if (B > 255)
            {
                B = 255;
            }

            int R = round(sqrt(pow(redX, 2) + pow(redY, 2)));
            if (R > 255)
            {
                R = 255;
            }

            int G = round(sqrt(pow(greenX, 2) + pow(greenY, 2)));
            if (G > 255)
            {
                G = 255;
            }

            temp[i][j].rgbtBlue = B;
            temp[i][j].rgbtRed = R;
            temp[i][j].rgbtGreen = G;
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }

    return;
}
