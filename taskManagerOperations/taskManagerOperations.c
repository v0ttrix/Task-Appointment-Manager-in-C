#include <stdbool.h>
/**
 * Task Manager Operations Implementation
 * Author: Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2
 * 
 * Core implementation of task management operations including CRUD functionality.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "taskManagerOperations.h"
#include "../taskUtilities/taskUtilities.h"

/* Global variables definition */
int taskCount = 0;
Task tasks[MAX_TASKS];

/**
 * Checks if the task array is at maximum capacity
 * @return: true if full, false otherwise
 */
bool isTaskArrayFull(void) {
    return taskCount >= MAX_TASKS;
}

/**
 * Validates if a task ID is within valid range
 * @param taskId: The task ID to validate
 * @return: true if valid, false otherwise
 */
bool isValidTaskId(int taskId) {
    return taskId >= 0 && taskId < taskCount;
}

/**
 * Prints formatted task details
 * @param taskId: The ID of the task to print
 */
void printTaskDetails(int taskId) {
    if (!isValidTaskId(taskId)) {
        printf("Invalid task ID: %d\n", taskId);
        return;
    }
    
    printf("%-4d %-30.30s %-12s\n", taskId, tasks[taskId].description, tasks[taskId].date);
}

/**
 * Adds a new task to the system
 * @return: true if successful, false otherwise
 */
bool addTask(void) {
    if (isTaskArrayFull()) {
        printf("Error: Task list is full! Cannot add more tasks.\n");
        return false;
    }
    
    char description[MAX_DESCRIPTION_LENGTH];
    char date[MAX_DATE_LENGTH];
    
    /* Get and validate task description */
    if (!getValidatedInput(description, sizeof(description), "Enter task description: ")) {
        printf("Error: Invalid description input.\n");
        return false;
    }
    
    /* Get and validate task date */
    do {
        if (!getValidatedInput(date, sizeof(date), "Enter task date (YYYY-MM-DD): ")) {
            printf("Error: Invalid date input.\n");
            return false;
        }
        
        if (!isValidDate(date)) {
            printf("Error: Invalid date format. Please use YYYY-MM-DD format.\n");
            continue;
        }
        break;
    } while (1);
    
    /* Store the validated task */
    strncpy(tasks[taskCount].description, description, MAX_DESCRIPTION_LENGTH - 1);
    tasks[taskCount].description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
    
    strncpy(tasks[taskCount].date, date, MAX_DATE_LENGTH - 1);
    tasks[taskCount].date[MAX_DATE_LENGTH - 1] = '\0';
    
    taskCount++;
    printf("Task added successfully! (ID: %d)\n", taskCount - 1);
    return true;
}

/**
 * Deletes a task from the system
 * @return: true if successful, false otherwise
 */
bool deleteTask(void) {
    if (taskCount == 0) {
        printf("No tasks available to delete.\n");
        return false;
    }
    
    printf("Current tasks:\n");
    displayAllTasks();
    
    int taskId = getValidatedInteger("Enter task ID to delete (0-%d): ", 0, taskCount - 1);
    
    if (!isValidTaskId(taskId)) {
        printf("Error: Invalid task ID.\n");
        return false;
    }
    
    /* Show task to be deleted */
    printf("\nTask to be deleted:\n");
    printf("ID: %d, Description: %s, Date: %s\n", 
           taskId, tasks[taskId].description, tasks[taskId].date);
    
    /* Confirm deletion */
    char confirm;
    printf("Are you sure you want to delete this task? (y/N): ");
    confirm = getchar();
    clearInputBuffer();
    
    if (tolower(confirm) != 'y') {
        printf("Task deletion cancelled.\n");
        return false;
    }
    
    /* Shift tasks to fill the gap */
    for (int i = taskId; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    
    taskCount--;
    printf("Task deleted successfully!\n");
    return true;
}

/**
 * Updates an existing task
 * @return: true if successful, false otherwise
 */
bool updateTask(void) {
    if (taskCount == 0) {
        printf("No tasks available to update.\n");
        return false;
    }
    
    printf("Current tasks:\n");
    displayAllTasks();
    
    int taskId = getValidatedInteger("Enter task ID to update (0-%d): ", 0, taskCount - 1);
    
    if (!isValidTaskId(taskId)) {
        printf("Error: Invalid task ID.\n");
        return false;
    }
    
    /* Show current task details */
    printf("\nCurrent task details:\n");
    printf("Description: %s\n", tasks[taskId].description);
    printf("Date: %s\n", tasks[taskId].date);
    
    char newDescription[MAX_DESCRIPTION_LENGTH];
    char newDate[MAX_DATE_LENGTH];
    
    /* Get new description */
    if (!getValidatedInput(newDescription, sizeof(newDescription), 
                          "Enter new description (or press Enter to keep current): ")) {
        /* Keep current description if input is empty */
        strcpy(newDescription, tasks[taskId].description);
    }
    
    /* Get new date */
    do {
        if (!getValidatedInput(newDate, sizeof(newDate), 
                              "Enter new date (YYYY-MM-DD) or press Enter to keep current: ")) {
            /* Keep current date if input is empty */
            strcpy(newDate, tasks[taskId].date);
            break;
        }
        
        if (!isValidDate(newDate)) {
            printf("Error: Invalid date format. Please use YYYY-MM-DD format.\n");
            continue;
        }
        break;
    } while (1);
    
    /* Update the task */
    strncpy(tasks[taskId].description, newDescription, MAX_DESCRIPTION_LENGTH - 1);
    tasks[taskId].description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
    
    strncpy(tasks[taskId].date, newDate, MAX_DATE_LENGTH - 1);
    tasks[taskId].date[MAX_DATE_LENGTH - 1] = '\0';
    
    printf("Task updated successfully!\n");
    return true;
}

/**
 * Searches for tasks containing a specific keyword
 */
void searchTasks(void) {
    if (taskCount == 0) {
        printf("No tasks available to search.\n");
        return;
    }
    
    char searchTerm[MAX_DESCRIPTION_LENGTH];
    
    if (!getValidatedInput(searchTerm, sizeof(searchTerm), "Enter search term: ")) {
        printf("Error: Invalid search term.\n");
        return;
    }
    
    /* Convert search term to lowercase for case-insensitive search */
    for (int i = 0; searchTerm[i]; i++) {
        searchTerm[i] = tolower(searchTerm[i]);
    }
    
    printf("\nSearch results for '%s':\n", searchTerm);
    
    bool found = false;
    for (int i = 0; i < taskCount; i++) {
        char lowerDescription[MAX_DESCRIPTION_LENGTH];
        strcpy(lowerDescription, tasks[i].description);
        
        /* Convert description to lowercase for comparison */
        for (int j = 0; lowerDescription[j]; j++) {
            lowerDescription[j] = tolower(lowerDescription[j]);
        }
        
        if (strstr(lowerDescription, searchTerm) != NULL) {
            if (!found) {
                printf("%-4s %-30s %-12s\n", "ID", "Description", "Date");
                printf("%-4s %-30s %-12s\n", "----", "------------------------------", "------------");
                found = true;
            }
            printTaskDetails(i);
        }
    }
    
    if (!found) {
        printf("No tasks found containing '%s'.\n", searchTerm);
    }
}
