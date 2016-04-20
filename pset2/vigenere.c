/**
 * caesar.c
 *
 * Evgeniy Kruglov
 * anklavez@gmail.com
 *
 * Program implements Vigenère cipher algorithm
 */

#include <ctype.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define LOWERCASE_ASCII_START 97
#define UPPERCASE_ASCII_START 65

int get_alphabet_position(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("%s\n","Wrong number of command line arguments!");
        return 1;
    }
    string keyword = argv[1];
    int keyword_len = strlen(keyword);
    for (int i = 0; i < keyword_len; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("%s\n","You provided non-alphabetical character!");
            return 1;
        }
    }
    string plaintext = GetString();
    int plaintext_len = strlen(plaintext);
    if (plaintext != NULL)
    {
        int j = 0;
        for (int i = 0; i < plaintext_len; i++)
        {
            if (isalpha(plaintext[i]))
            {
                int p = get_alphabet_position(plaintext[i]);
                int k = get_alphabet_position(keyword[j]);
                // main formula
                int offset = (p + k) % 26;
                int encrypted_symbol;
                if (isupper(plaintext[i]))
                {
                    encrypted_symbol = offset + UPPERCASE_ASCII_START;
                }else
                {
                    encrypted_symbol = offset + LOWERCASE_ASCII_START;
                }
                printf("%c",encrypted_symbol);
                j++;
            }else
            {
                printf("%c",(plaintext[i]));
            }
            if ((j % keyword_len) == 0)
            {
                j = 0;
            }
        }
        printf("\n");
    }
    return 0;
    
}

/**
 * Function return position of character in English alphabet, started from 0
 */
int get_alphabet_position(char c)
{
    char lower_value = tolower(c);
    int position = (lower_value - 'a');
    return position;
}