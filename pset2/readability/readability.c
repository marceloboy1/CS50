#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //variable declarations
    string texto = get_string("Text: ");
    int letras = 0;
    int palavras = 1;
    int frases = 0;
    //int letra = 0;
    int len = 0;

    //loops trough the text
    while (texto[len] != 0)
    {
        len++;
    }

    for (int i = 0; i < len; i++)
    {
        //if script encounter ponctuation marks, it adds a sentence
        if ((texto[i] == 46) || (texto[i] == 33) || (texto[i] == 63))
        {
            frases++;

        }

        //if it encounters a space, adds a word
        else if (texto[i] == 32)
        {
            palavras++;

        }

        //and add letters for all chars
        else if (((texto[i] >= 65) && (texto[i] <= 90)) || ((texto[i] >= 97) && (texto[i] <= 122)))
        {
            letras++;
        }

    }

    //doing some math stuff
    float l = ((letras * 100.00) / palavras);
    float s = ((frases * 100.00) / palavras);
    float index = ((0.0588 * l) - (0.296 * s) - 15.8);
    int grade = round(index);

    //showing the results
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}