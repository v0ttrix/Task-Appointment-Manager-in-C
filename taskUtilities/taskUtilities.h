/**
 * Task Utilities Header
 * Author: Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2
 * 
 * Utility functions for task validation and helper operations.
 */

#ifndef TASK_UTILITIES_H
#define TASK_UTILITIES_H

#include <stdbool.h>

/* Date validation function */
bool isValidDate(const char* date);

/* Input validation helpers */
bool getValidatedInput(char* buffer, int maxLength, const char* prompt);
void clearInputBuffer(void);
int getValidatedInteger(const char* prompt, int min, int max);

#endif /* TASK_UTILITIES_H */
