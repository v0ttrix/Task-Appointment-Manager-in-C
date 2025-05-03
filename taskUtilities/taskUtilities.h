//Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2

#pragma once // ensures the file is included only once

#ifndef TASK_UTILITIES_H // checks if TASK_UTILITIES_H is not defined
#define TASK_UTILITIES_H // defines TASK_UTILITIES_H to avoid multiple inclusions

// function prototype for validating a date
// takes a const char* as input (date in string format)
// returns an int: 1 if the date is valid, 0 otherwise
int isValidDate(const char* date);

#endif // ends the TASK_UTILITIES_H conditional inclusion
