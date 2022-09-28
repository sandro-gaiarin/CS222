#include <stdio.h>
int main()
{
    int number;
    printf("Enter an integer: ");
    scanf("%d", &number);
    // Is the number negative?
    if (number < 0)
    {
        printf("%d is negative.\n", number);
    }
    // Is the number positive?
    else if (number > 0)
    {
        printf("%d is positive.\n", number);
    }
    else // If we're here, then number is 0.
    {
        printf("%d is zero.\n", number);
    }
    // Determine if number is a multiple of 3
    if (number % 3 == 0)
    {
        printf("%d is a multiple of 3.\n", number);
    }
    else
    {
        printf("%d is not a multiple of 3.\n", number);
    }
    return 0;
}