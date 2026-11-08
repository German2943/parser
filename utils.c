#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
char *string_divider(FILE *f) // reads the input file and makes an array with all its characters
{

    int capacidad = 100;
    int elementos = 0;
    char *ptr = (char *)malloc(sizeof(char) * capacidad);
    char *tmp;

    int c;
    int iteration = 0;
    while ((c = fgetc(f)) != EOF)
    {
        if (elementos >= capacidad)
        {
            capacidad = capacidad * 2;
            tmp = (char *)realloc(ptr, capacidad);
            ptr = tmp;
        }

        ptr[iteration] = (char)c;
        elementos++;
        iteration++;
    }
    ptr[elementos] = '\0';
    return ptr;
}
