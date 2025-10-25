/**
 * Task Manager Operations Header
 * Author: 
 * 
 * This header defines the core data structures and function prototypes
 * for task management operations including CRUD operations and search functionality.
 */
#ifndef TASK_MANAGER_OPERATIONS_H
#define TASK_MANAGER_OPERATIONS_H
#include <stdbool.h>
/* Constants */
#define MAX_TASKS 100
#define MAX_DESCRIPTION_LENGTH 100
#define MAX_DATE_LENGTH 11
/* Task structure definition */
typedef struct {
    char description[MAX_DESCRIPTION_LENGTH];
    char date[MAX_DATE_LENGTH];
} Task;
/* Global variables - extern declarations */
extern int taskCount;
extern Task tasks[MAX_TASKS];
/* Function prototypes for task operations */
bool addTask(void);
bool deleteTask(void);
bool updateTask(void);
void displaySingleTask(void);
void displayTasksInRange(void);
void displayAllTasks(void);
void searchTasks(void);
/* Helper functions */
bool isTaskArrayFull(void);
bool isValidTaskId(int taskId);
void printTaskDetails(int taskId);
#endif /* TASK_MANAGER_OPERATIONS_H */
