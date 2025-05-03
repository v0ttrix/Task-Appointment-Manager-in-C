//Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2

#include <stdio.h> // for standard input/output (not used here but might be useful later)
#include <string.h> // for string functions just like strlen
#include "../taskUtilities/taskUtilities.h" // includes the header file where isValidDate is declared

int isValidDate(const char* date) 
{
    // checks if the date string has exactly 10 characters (YYYY-MM-DD)
    if (strlen(date) != 10) return 0; // if not, it's invalid

    // checks if the 5th and 8th characters are '-' as expected in YYYY-MM-DD
    if (date[4] != '-' || date[7] != '-') return 0;

    // loops through each character in the date string
    for (int i = 0; i < 10; i++) 
    {
        // skips the '-' characters at positions 4 and 7
        if (i == 4 || i == 7) continue;

        // ensures all other characters are digits ('0' to '9')
        if (date[i] < '0' || date[i] > '9') return 0;
    }

    // if all checks pass, the date is valid
    return 1;
}
