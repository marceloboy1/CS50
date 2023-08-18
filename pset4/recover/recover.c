#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;

    //checks the argmuments
    if (argc < 2)
    {
        printf("Usage: ./recover FILE.RAW\n\n");
        return 1;
    }

    //variable declarations
    FILE *file = fopen(argv[1], "r");
    BYTE buffer[512];
    int counter = 0;
    char *fileName = malloc(1);

    //checks if the file is valid
    FILE *img;
    if (file == NULL)
    {
        printf("Arquivo inválido\n");
        return 1;
    }

    //iterate trough file
    while (fread(buffer, 512, 1, file) == 1)
    {
        //if jpeg signature found, creates a new file
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            //for the firts file
            if (counter == 0)
            {
                sprintf(fileName, "%03i.jpg", counter);
                img = fopen("000.jpg", "w");
                fwrite(buffer, 512, 1, img);
                counter++;
            }

            //all other files
            else
            {
                fclose(img);
                sprintf(fileName, "%03i.jpg", counter);
                counter ++;
                img = fopen(fileName, "w");
                fwrite(buffer, 512, 1, img);
            }
        }

        //continue writing unitl find a new jpeg
        else
        {
            if (counter > 0)
            {
                fwrite(buffer, 512, 1, img);
            }

        }
    }

    //clear memory
    fclose(img);
    fclose(file);
    free(fileName);
}