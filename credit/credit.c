#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit, temp_credit;
    do
    {
        credit = get_long("Number: ");
    }
    while (!(0 < credit && credit < 9999999999999999));
    temp_credit = credit;
    int digits = 0, sum = 0, first_digit, second_digit, last_digit = 0;
    bool valid_cc = false;
    while (temp_credit != 0)
    {
        digits++;
        temp_credit /= 10;
    }
    temp_credit = credit;
    int credit_arr[digits];

    for (int i = digits - 1; i >= 0; i--)
    {
        last_digit = temp_credit % 10;
        credit_arr[i] = last_digit;
        temp_credit /= 10;
        if (i == 1)
        {
            second_digit = last_digit;
        }
        else if (i == 0)
        {
            first_digit = last_digit;
        }
    }

    for (int i = digits - 1, j = 0; i >= 0; i--, j++)
    {
        if (j % 2 != 0)
        {
            int num = credit_arr[i] * 2;
            if (num > 9)
            {
                int num_1 = num % 10;
                int num_2 = num / 10;
                num = num_1 + num_2;
            }
            sum += num;
        }
    }

    for (int i = digits - 1, j = 0; i >= 0; i--, j++)
    {
        if (j % 2 == 0)
        {
            sum += credit_arr[i];
        }
    }

    if (sum % 10 == 0)
    {
        valid_cc = true;
    }

    if (valid_cc)
    {
        // VISA
        if (first_digit == 4 && (digits == 13 || digits == 16))
        {
            printf("VISA\n");
        }
        // MASTERCARD
        else if ((first_digit == 5 &&
                (second_digit == 1 || second_digit == 2 || second_digit == 3 ||
                second_digit == 4 || second_digit == 5)) &&
                    digits == 16)
        {
            printf("MASTERCARD\n");
        }
        // AMEX
        else if ((first_digit == 3 && (second_digit == 4 || second_digit == 7)) && digits == 15)
        {
            printf("AMEX\n");
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
    return 0;
}
