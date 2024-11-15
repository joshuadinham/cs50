#include <ctype.h>
#include <string.h>
#include <cs50.h>
#include <stdio.h>

bool is_unique_alpha(string key);
const char* encrypt(string plaintext, string key, char* encrypted);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: argv[0] key\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        if(strlen(key) != 26)
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }
        else if (!is_unique_alpha(key))
        {
            printf("Key must contain all unique alphabetic characters\n");
            return 1;
        }
        else
        {
            for (int i = 0; key[i] != '\0'; i++)
            {
                key[i] = toupper(key[i]);
            }
        }

        string plaintxt = get_string("plaintext:  ");
        char encrypted[strlen(plaintxt)+1];
        printf("ciphertext: %s\n", encrypt(plaintxt, key, encrypted));
    }
    return 0;
}

bool is_unique_alpha(string key)
{
    char saved_chars[27] = {};
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (isalpha(key[i]))
        {
            char c = toupper(key[i]);
            int index = c - 'A';
            if(!saved_chars[index])
            {
                saved_chars[index] = c;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

const char* encrypt(string txt, string key, char* encrypted)
{
    char c;
    int len = strlen(txt);

    for (int i = 0; i < len; i++)
    {
        if (ispunct(txt[i]) || isdigit(txt[i]) || isspace(txt[i]))
        {
            encrypted[i] = txt[i];
        }
        else
        {
            char upper = toupper(txt[i]);
            int index = upper - 'A';
            if (isupper(txt[i]))
            {
                encrypted[i] = key[index];
            }
            else
            {
                encrypted[i] = tolower(key[index]);
            }
        }
    }
    encrypted[len] = '\0';
    return encrypted;
}

