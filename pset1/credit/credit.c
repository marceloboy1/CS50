#include <cs50.h>
#include <stdio.h>

int main(void)
{

    //asks user for card number
    long cardNumber = get_long("Number:");

    //variable declaration
    int sumP = 0;
    int sum = 0;
    int sumI = 0;
    int counter = 0;
    int company = 0;


    do
    {
        //checks if we are on even or uneaven position
        //even position just add the last digit to the sumP
        if (counter % 2 == 0)
        {
            sumP += cardNumber % 10;
        }

        //uneven pos multiplies last digit by two, the add to the sumI if lower then 10. If graeter, then add the two digits togeter before add do sumI
        else
        {
            if ((cardNumber % 10) * 2 >= 10)
            {
                int digit = ((cardNumber % 10) * 2);
                digit = (digit % 10) + (digit / 10);
                sumI += digit;
            }
            else
            {
                sumI += (cardNumber % 10) * 2;
            }
        }

        if ((cardNumber >= 10) && (cardNumber < 100))
        {
            company = cardNumber;
        }

        counter++;
        cardNumber = cardNumber / 10;
    }
    while (cardNumber >= 1);

    //checks the validation and print results
    sum = sumP + sumI;

    if ((sum % 10) == 0)
    {
        //CHECK FOR AMEX
        if (((company == 34) || (company == 37)) && (counter == 15))
        {
            printf("AMEX\n");
        }

        //CHECK FOR MASER
        else if (((company >= 51) && (company <= 55)) && (counter == 16))
        {
            printf("MASTERCARD\n");
        }

        //CHECK FOR VISA
        else if (((company / 10) == 4) && ((counter == 13) || (counter == 16)))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}
