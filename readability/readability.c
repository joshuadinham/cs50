#include <cs50.h>
#include <math.h>
#include <stdio.h>

int get_grade_level(string text);

int main(void)
{
    string text = get_string("Text: ");
    int grade = get_grade_level(text);
    if (grade <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}

int get_grade_level(string text)
{
    int words = 0, sentences = 0, letters = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
        else if (text[i] == ' ')
        {
            words += 1;
        }
        else if ((65 <= text[i] && text[i] <= 90) || (97 <= text[i] && text[i] <= 122))
        {
            letters += 1;
        }
    }

    words += 1;
    float avg_letters = (letters / (float) words) * 100.0,
          avg_sentences = (sentences / (float) words) * 100.0;
    float g_index = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;

    return round(g_index);
}

