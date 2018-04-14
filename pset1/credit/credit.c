#include <stdio.h>
#include <cs50.h>

/**
 * Example:
 *
 * 378282246310005
 *  - - - - - - -
 *
 * 0*2 + 0*2 + 3*2 + 4*2 + 2*2 + 2*2 + 7*2 = 27
 *
 * 378282246310005
 * - - - - - - - -
 *
 * 3 + 8 + 8 + 2 + 6 + 1 + 0 + 5 = 33
 *
 * 27 + 33 = 60
 *
 * 60 % 10 == 0 / VALID CARD
 *
 */

int main()
{
    long long cc_number = get_long_long("Number: ");
    int digit1 = 0, digit2 = 0, num_digits = 0, sum_of_double_odds = 0, sum_of_evens = 0;

    while (cc_number > 0)
    {
        digit2 = digit1;
        digit1 = cc_number % 10;

        if (num_digits % 2 == 0)
        {
            sum_of_evens += digit1;
        }
        else
        {
            int multiple = 2 * digit1;
            sum_of_double_odds += (multiple / 10) + (multiple % 10);
        }

        cc_number /= 10;
        num_digits++;
    }

    bool is_valid = (sum_of_evens + sum_of_double_odds) % 10 == 0;
    int first_two_digits = (digit1 * 10) + digit2;

    if (digit1 == 4 && num_digits >= 13 && num_digits <= 16 && is_valid)
    {
        printf("VISA\n");
    }
    else if (first_two_digits >= 51 && first_two_digits <= 55 && num_digits == 16 && is_valid)
    {
        printf("MASTERCARD\n");
    }
    else if ((first_two_digits == 34 || first_two_digits == 37) && num_digits == 15 && is_valid)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
