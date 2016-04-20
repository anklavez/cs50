/**
 * caesar.c
 *
 * Evgeniy Kruglov
 * anklavez@gmail.com
 *
 * Program implements Caesar cipher algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>


int get_alphabet_position(char c);

#define LOWERCASE_ASCII_START 97
#define UPPERCASE_ASCII_START 65

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("%s\n","wrong number of command line arguments!");
        return 1;
    }
    
    int k = atoi(argv[1]);
    if (k > 0)
    {
        string plaintext = GetString();
        if (plaintext != NULL)
        {
            int n = strlen(plaintext);
            for (int i = 0; i < n; i++)
            {
                if (isalpha(plaintext[i]))
                {
                    int position = get_alphabet_position(plaintext[i]);
                    int offset = (position + k) % 26;
                    int encrypted_symbol;
                    if (isupper(plaintext[i]))
                    {
                        encrypted_symbol = offset + UPPERCASE_ASCII_START;
                    }else
                    {
                        encrypted_symbol = offset + LOWERCASE_ASCII_START;
                    }
                    printf("%c",encrypted_symbol);
                }else
                {
                    printf("%c",(plaintext[i]));
                }    
            }
            printf("\n");
        }
    }else
    {
        return 1;
    }
    
}

/**
 * Function return position of character in English alphabet
 */
int get_alphabet_position(char c)
{
    char lower_value = tolower(c);
    int position = (lower_value - 'a');
    return position;
}
