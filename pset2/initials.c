/**
 * initials.c
 *
 * Evgeniy Kruglov
 * anklavez@gmail.com
 *
 * Print initials from user input.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // user input
    string initials = GetString();

    if (initials != NULL)
    {
        char* pch;
        pch = strtok (initials," ");
        while (pch != NULL)
        {  
            printf("%c", toupper(pch[0]));
            pch = strtok (NULL, " ");
        }
        printf("\n");
    }
}