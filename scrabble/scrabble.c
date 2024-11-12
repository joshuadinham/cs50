#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int scrabble_points(string word);
int letter_to_points(char letter);

int main(void)
{
    string player_1 = get_string("Player 1: ");
    string player_2 = get_string("Player 2: ");

    int player_1_points = scrabble_points(player_1);
    int player_2_points = scrabble_points(player_2);

    if (player_1_points > player_2_points)
    {
        printf("Player 1 wins!");
    }
    else if (player_2_points > player_1_points)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }

    return 0;
}

int scrabble_points(string word)
{
    int sum = 0, num = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        num = letter_to_points(word[i]);
        sum += num;
    }

    return sum;
}

int letter_to_points(char letter)
{
    char letters[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
    int points[27] = {1, 3,	3,	2,	1,	4,	2,	4,	1,	8,	5,	1,	3,	1,	1,	3,	10,	1,	1,	1,	1,	4,	4,	8,	4,	10};

    for (int i = 0; letters[i] != '\0'; i++)
    {
        if (letters[i] == toupper(letter))
        {
            return points[i];
        }
    }

    return 0;
}


