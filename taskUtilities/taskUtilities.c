/**
 * Task Utilities Implementation
 * Author: Jaden Mardini
 * Author: 
 * 
 * Implementation of utility functions for input validation and date handling.
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "taskUtilities.h"
/**
 * Validates date format and basic date constraints
 * @param date: Date string in YYYY-MM-DD format
 * @return: true if valid, false otherwise
 */
bool isValidDate(const char* date) {
    if (!date || strlen(date) != 10) {
        return false;
    }
    
    /* Check format: YYYY-MM-DD */
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    
    /* Validate all digits except hyphens */
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) {
            return false;
        }
    }
    
    /* Extract and validate year, month, day */
    int year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + 
               (date[2] - '0') * 10 + (date[3] - '0');
    int month = (date[5] - '0') * 10 + (date[6] - '0');
    int day = (date[8] - '0') * 10 + (date[9] - '0');
    
    /* Basic range validation */
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    /* Month-specific day validation */
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    /* Check for leap year */
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }
    
    return day <= daysInMonth[month - 1];
}
/**
 * Gets validated input from user with length checking
 * @param buffer: Buffer to store input
 * @param maxLength: 
 * @param prompt: Prompt message for user
 * @return: true if input is valid, false otherwise
 */
bool getValidatedInput(char* buffer, int maxLength, const char* prompt) {
    if (!buffer || !prompt || maxLength <= 0) {
        return false;
    }
    
    printf("%s", prompt);
    
    if (!fgets(buffer, maxLength, stdin)) {
        return false;
    }
    
    /* Remove trailing newline */
    buffer[strcspn(buffer, "\n")] = '\0';
    
    /* Check if input is empty */
    if (strlen(buffer) == 0) {
        return false;
    }
    
    return true;
}
/**
 * Clears the input buffer to handle leftover characters
 */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
/**
 * Gets a validated integer within specified range
 * @param prompt: Prompt message for user
 * @param min: Minimum allowed value
 * @param max: 
 * @return: Valid integer within range
 */
int getValidatedInteger(const char* prompt, int min, int max) {
    int value;
    int result;
    
    do {
        printf("%s", prompt);
        result = scanf("%d", &value);
        clearInputBuffer();
        
        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        if (value < min || value > max) {
            printf("Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        
        break;
    } while (1);
    
    return value;
}
