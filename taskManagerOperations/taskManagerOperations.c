//Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2

#define _CRT_SECURE_NO_WARNINGS // disables warnings for unsafe functions like scanf and fgets on Windows

#include "../testTaskManagerAppfunctions/pch.h" // precompiled header for faster compilation
#include <stdio.h> // standard input/output functions
#include <string.h> // for string manipulation (like strcmp, fgets)
#include <stdlib.h> // for system calls like malloc or exit
#include "../taskStorageHandler/taskStorageHandler.h" // handles loading/saving tasks
#include "../taskUtilities/taskUtilities.h" // utility functions like date validation
#include "taskManagerOperations.h" // task operations like add, delete, update

#define MAX_TASKS 100 // maximum number of tasks allowed

int taskCount = 0;            // global variable to keep track of the number of tasks
Task tasks[MAX_TASKS];        // global array to store all tasks

void addTask()
{
    // checks if the task array is full
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return; // exits early if no more tasks can be added
    }

    // prompt the user to enter the task description
    printf("Enter task description: ");
    fgets(tasks[taskCount].description, 100, stdin); // reads the description
    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = '\0'; // removes trailing newline

    // prompt the user to enter the task date
    printf("Enter task date (YYYY-MM-DD): ");
    fgets(tasks[taskCount].date, 11, stdin); // reads the date
    tasks[taskCount].date[strcspn(tasks[taskCount].date, "\n")] = '\0'; // removes trailing newline

    taskCount++; // increments the task counter
    printf("Task added successfully.\n"); // confirms the task was added
}

void deleteTask()
{
    int taskId;
    // prompts the user to enter the task ID to delete
    printf("Enter task ID to delete (0-%d): ", taskCount - 1);
    scanf_s("%d", &taskId); // reads the ID
    (void)getchar();  // consumes the newline character left by scanf_s

    // validates the entered task ID
    if (taskId < 0 || taskId >= taskCount) 
    {
        printf("Invalid task ID.\n");
        return; // exits if the ID is invalid
    }

    // shifts tasks down to fill the gap left by the deleted task
    for (int i = taskId; i < taskCount - 1; i++) 
    {
        tasks[i] = tasks[i + 1];
    }
    taskCount--; // decrements the task counter
    printf("Task deleted successfully.\n"); // confirms deletion
}

void updateTask() {
    int taskId;
    // prompts the user to enter the task ID to update
    printf("Enter task ID to update (0-%d): ", taskCount - 1);
    scanf_s("%d", &taskId);
    (void)getchar();  // consumes the newline character left by scanf_s

    // validates the entered task ID
    if (taskId < 0 || taskId >= taskCount) 
    {
        printf("Invalid task ID.\n");
        return; // exits if the ID is invalid
    }

    // prompts the user for a new task description
    printf("Enter new task description: ");
    fgets(tasks[taskId].description, 100, stdin);
    tasks[taskId].description[strcspn(tasks[taskId].description, "\n")] = '\0'; // removes trailing newline

    // prompts the user for a new task date
    printf("Enter new task date (YYYY-MM-DD): ");
    fgets(tasks[taskId].date, 11, stdin);
    tasks[taskId].date[strcspn(tasks[taskId].date, "\n")] = '\0';

    printf("Task updated successfully.\n"); // confirms the task was updated
}

void displaySingleTask() {
    int taskId;
    // prompts the user to enter the task ID to display
    printf("Enter task ID to display (0-%d): ", taskCount - 1);
    scanf_s("%d", &taskId);
    (void)getchar();  // consumes the newline character left by scanf_s

    // validates the entered task ID
    if (taskId < 0 || taskId >= taskCount) 
    {
        printf("Invalid task ID.\n");
        return; // exits if the ID is invalid
    }

    // displays the task details
    printf("Task ID: %d\n", taskId);
    printf("Description: %s\n", tasks[taskId].description);
    printf("Date: %s\n", tasks[taskId].date);
}

void displayTasksInRange() 
{
    char startDate[11], endDate[11];

    // prompts the user for the start date
    printf("Enter start date (YYYY-MM-DD): ");
    fgets(startDate, sizeof(startDate), stdin);
    startDate[strcspn(startDate, "\n")] = '\0'; // removes trailing newline

    // prompts the user for the end date
    printf("Enter end date (YYYY-MM-DD): ");
    fgets(endDate, sizeof(endDate), stdin);
    endDate[strcspn(endDate, "\n")] = '\0'; // removes trailing newline

    printf("\nDisplaying tasks between %s and %s:\n", startDate, endDate);

    int found = 0;  // tracks if any tasks fall within the range
    for (int i = 0; i < taskCount; i++) {
        // checks if the task date falls within the range
        if (strcmp(tasks[i].date, startDate) >= 0 && strcmp(tasks[i].date, endDate) <= 0) 
        {
            printf("Task ID: %d\n", i);
            printf("Description: %s\n", tasks[i].description);
            printf("Date: %s\n", tasks[i].date);
            printf("---------------------------\n");
            found = 1; // marks that at least one task was found
        }
    }

    // if no tasks are found, informs the user
    if (!found) 
    {
        printf("No tasks found in the specified date range.\n");
    }
}

void displayAllTasks()
{
    // checks if there are no tasks to display
    if (taskCount == 0) 
    {
        printf("No tasks available.\n");
        return; // exits early
    }

    printf("Displaying all tasks:\n");
    for (int i = 0; i < taskCount; i++)
    {
        // displays each task's details
        printf("Task ID: %d\n", i);
        printf("Description: %s\n", tasks[i].description);
        printf("Date: %s\n", tasks[i].date);
    }
}

void searchTasks() 
{
    char searchTerm[100];
    // prompts the user for a search term
    printf("Enter search term: ");
    fgets(searchTerm, 100, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = '\0'; // removes trailing newline

    printf("Searching for tasks containing '%s':\n", searchTerm);
    for (int i = 0; i < taskCount; i++) 
    {
        // checks if the description contains the search term
        if (strstr(tasks[i].description, searchTerm) != NULL) {
            printf("Task ID: %d\n", i);
            printf("Description: %s\n", tasks[i].description);
            printf("Date: %s\n", tasks[i].date);
        }
    }
}
