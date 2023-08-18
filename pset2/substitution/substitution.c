#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    //functions declarations
    int getLen(string text);
    bool allAlphas(string text);
    bool isUnique(string key);
    void cypher(string text, string key);

    //variables declarations
    string key = argv[1];

    //CLI argument tests
    if ((argc != 2) || (getLen(key) != 26) || (allAlphas(key) == false) || (isUnique(key) != true))
    {
        printf("The key must contain the 26 alphabet unique letters\n");
        return (1);
    }

    //Main Loop
    else
    {
        string plainText = get_string("plaintext: ");
        cypher(plainText, key);
        return (0);
    }

}

//Get the string length
int getLen(string text)
{
    int keyLen = 0;
    for (int i = 0; text[i] != 0; i++)
    {
        keyLen++;
    }
    return (keyLen);
}

//test to see if all key chars are alphabetic
bool allAlphas(string text)
{
    bool allAlpha = true;
    for (int i = 0; text[i] != 0; i++)
    {
        if (isalpha(text[i]) == 0)
        {
            allAlpha = false;
        }
    }
    return (allAlpha);
}

//main encription function
void cypher(string text, string key)
{
    int lenText = getLen(text);
    int lenKey = getLen(key);
    for (int i = 0; i < lenText; i++)
    {
        //handles only with alphabetic chars
        if (isalpha(text[i]) != 0)
        {
            //lower case
            if (islower(text[i]) != 0)
            {
                int letter = text[i] - 97;
                text[i] = tolower(key[letter]);
            }

            //upper case
            else
            {
                int letter = text[i] - 65;
                text[i] = toupper(key[letter]);
            }
        }
    }

    //output
    printf("ciphertext: %s\n", text);
}

//check the key for repeated values
bool isUnique(string key)
{
    for (int i = 0; i < getLen(key); i++)
    {
        for (int j = 0; j < getLen(key); j++)
        {
            if (tolower((key[i]) == tolower(key[j])) && (i != j))
            {
                return false;
            }
            else if ((key[i] == key[j]) && (i != j))
            {
                return false;
            }
        }
    }
    return true;
}