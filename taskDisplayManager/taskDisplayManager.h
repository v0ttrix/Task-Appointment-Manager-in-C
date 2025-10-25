/**
 * Task Display Manager Header
 * Author: Max - PROG71990 - f24 - Sec 1 - Group 2
 * 
 * Functions for displaying task information in various formats.
 */

#ifndef TASK_DISPLAY_MANAGER_H
#define TASK_DISPLAY_MANAGER_H

/* Display functions */
void displaySingleTask(void);
void displayTasksInRange(void);
void displayAllTasks(void);

/* Helper display functions */
void printTaskHeader(void);
void printTaskSeparator(void);

#endif /* TASK_DISPLAY_MANAGER_H */