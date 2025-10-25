/**
 * Task Display Manager Implementation
 * Author: Max - PROG71990 - f24 - Sec 1 - Group 2
 * 
 * Implementation of display functions for task information.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "taskDisplayManager.h"
#include "../taskManagerOperations/taskManagerOperations.h"
#include "../taskUtilities/taskUtilities.h"

/**
 * Prints a formatted header for task display
 */
void printTaskHeader(void) {
    printf("\n%-4s %-30s %-12s\n", "ID", "Description", "Date");
    printTaskSeparator();
}

/**
 * Prints a separator line for task display
 */
void printTaskSeparator(void) {
    printf("%-4s %-30s %-12s\n", "----", "------------------------------", "------------");
}

/**
 * Displays a single task by ID
 */
void displaySingleTask(void) {
    if (taskCount == 0) {
        printf("No tasks available to display.\n");
        return;
    }
    
    int taskId = getValidatedInteger("Enter task ID to display (0-%d): ", 0, taskCount - 1);
    
    if (!isValidTaskId(taskId)) {
        printf("Invalid task ID.\n");
        return;
    }
    
    printTaskHeader();
    printTaskDetails(taskId);
}

/**
 * Displays tasks within a specified date range
 */
void displayTasksInRange(void) {
    if (taskCount == 0) {
        printf("No tasks available to display.\n");
        return;
    }
    
    char startDate[MAX_DATE_LENGTH];
    char endDate[MAX_DATE_LENGTH];
    
    /* Get and validate start date */
    do {
        if (!getValidatedInput(startDate, sizeof(startDate), "Enter start date (YYYY-MM-DD): ")) {
            printf("Invalid input. Please try again.\n");
            continue;
        }
        if (!isValidDate(startDate)) {
            printf("Invalid date format. Please use YYYY-MM-DD.\n");
            continue;
        }
        break;
    } while (1);
    
    /* Get and validate end date */
    do {
        if (!getValidatedInput(endDate, sizeof(endDate), "Enter end date (YYYY-MM-DD): ")) {
            printf("Invalid input. Please try again.\n");
            continue;
        }
        if (!isValidDate(endDate)) {
            printf("Invalid date format. Please use YYYY-MM-DD.\n");
            continue;
        }
        if (strcmp(endDate, startDate) < 0) {
            printf("End date must be after or equal to start date.\n");
            continue;
        }
        break;
    } while (1);
    
    printf("\nTasks between %s and %s:\n", startDate, endDate);
    
    bool found = false;
    printTaskHeader();
    
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].date, startDate) >= 0 && strcmp(tasks[i].date, endDate) <= 0) {
            printTaskDetails(i);
            found = true;
        }
    }
    
    if (!found) {
        printf("No tasks found in the specified date range.\n");
    }
}

/**
 * Displays all tasks in the system
 */
void displayAllTasks(void) {
    if (taskCount == 0) {
        printf("No tasks available to display.\n");
        return;
    }
    
    printf("\nAll Tasks (%d total):\n", taskCount);
    printTaskHeader();
    
    for (int i = 0; i < taskCount; i++) {
        printTaskDetails(i);
    }
}