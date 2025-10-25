/**
 * Task Storage Handler Header
 * Author: YashB - PROG71990 - Fall2024 - Group 2 - Project
 * 
 * Functions for persistent storage of task data to/from disk.
 */

#ifndef TASK_STORAGE_HANDLER_H
#define TASK_STORAGE_HANDLER_H

#include <stdbool.h>

/* Storage file configuration */
#define STORAGE_FILENAME "tasks.dat"

/* Storage operation functions */
bool loadDataFromDisk(void);
bool saveDataToDisk(void);

#endif /* TASK_STORAGE_HANDLER_H */