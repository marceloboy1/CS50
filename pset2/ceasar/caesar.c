#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    //validade the command line arguments
    bool isDigit = true;
    int n = 0;
    while (argv[1][n] != 0) {
            if (isdigit(argv[1][n]) == false)
            {
                isDigit = false;
                break;
            }
            n++;
        }

    if ((argc != 2) || (isDigit == false))
    {
        printf("Usage: ./ceasar key\n");
    }


    else
    {
        //functions placeholder
        int len(string text);
        string cypher(string text, int k);
        int k = atoi(argv[1]);
        string text = get_string("plaintext: ");
        printf("encrypted: %s\n", cypher(text, k));
    }
}


//Calcula o tamanho do texto inserido
int len(string text)
{
    int counter = 0;
    while (text[counter] != 0)
    {
        counter++;
    }
    return(counter);
}

string cypher(string text, int k)
{
    char rotate(char c, int k);
    int key = k;
    int size = len(text);

    for (int i = 0; i < size; i++){
        text[i] = rotate(text[i], k);
    }
    return(text);
}

char rotate(char c, int k)
{


    //printf("Letter %i\n", c+k);
    if (islower(c) > 0)
    {
        if ((c+k) > 122)
        {
        //    printf("IS LOWER + 122");
            c = ((c+k)-96)%26;
            printf("%i\n\n", ((c+k)-96)%26);
        }
        else
        {
      //      printf("IS LOWER - 122");
            c = (c+k);
        }
    }

    else if (isupper(c) > 0)
    {
        if ((c+k) > 90)
        {
            printf("IS UPPER + 90");
            printf("c: %i\n k: %i\n result: %i\n", c,((c+k)-64)%26);
            c = ((c+k)-64)%26;
        }
        else
        {
       //     printf("IS UPPER - 90");
            c = (c+k);
        }
    }
    //printf("Char %c\n", c);
    return(c);
}

// int tenPower(int number, int power)
// {
//     for (int i =0; i < power; i++)
//     {
//         number *= number;
//     }
//     return(number);
// }

// int toInt(string keyString)
// {
//     int size = len(keyString);
//     int key = 0;
//     if (size > 1)
//     {
//         for (int i = 0; i < size; i++)
//         {
//             printf("TESTE: %i\n", power(10,3));
//             printf("Digito: %i\n", (keyString[i]-48));
//             printf("Potencia: %i\n", (size-i));
//             printf("Valor: %i\n\n", (keyString[i]-48)*(power(10,3)));
//             key += (keyString[i]-48)*(10^(size-i));
//         }
//     }
//     //printf("Power: %i\n", 10^(size-1));
//     //printf("Size: %i\n", size);
//     printf("Key: %i\n", key);
//     return(key);
// }