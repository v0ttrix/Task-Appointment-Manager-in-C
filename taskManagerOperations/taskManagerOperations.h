//Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2

#pragma once // ensures this header file is included only once in the compilation process

#ifndef TASK_MANAGER_OPERATIONS_H // if TASK_MANAGER_OPERATIONS_H is not defined
#define TASK_MANAGER_OPERATIONS_H // define it now to avoid multiple inclusions

#define MAX_TASKS 100 // maximum number of tasks the program can handle

// defining the Task structure
typedef struct 
{
    char description[100]; // stores the task description (up to 99 characters + null terminator)
    char date[11];  // stores the task date in the format YYYY-MM-DD (10 characters + null terminator)
} Task;

// external declarations for shared variables
extern int taskCount; // keeps track of the number of tasks currently in memory
extern Task tasks[MAX_TASKS]; // array to hold all tasks (declared here, defined in a .c file)

// function prototypes for task operations
void addTask(); // adds a new task
void deleteTask(); // deletes a task based on user input
void updateTask(); // updates an existing task
void displaySingleTask(); // displays the details of one specific task
void displayTasksInRange(); // shows tasks within a given date range
void displayAllTasks(); // lists all tasks currently stored
void searchTasks(); // searches for tasks based on a keyword

#endif // ends the TASK_MANAGER_OPERATIONS_H conditional inclusion
