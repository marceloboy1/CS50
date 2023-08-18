#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    //asks user for heith value
    while ((height < 1) || (height > 8))
    {
        height = get_int("Heigth:");
    }

    //iterate trough heigth printing the lines
    for (int i = 0; i < height; i++)
    {

        for (int j = height - i; j > 1; j--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = i; j >= 0; j--)
        {
            printf("#");
        }

        //create a new line
        printf("\n");


    }

}