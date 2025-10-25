#include <stdbool.h>
/**
 * Task Storage Handler Implementation
 * Author: 
 * 
 * Implementation of persistent storage operations for task data.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "taskStorageHandler.h"
#include "../taskManagerOperations/taskManagerOperations.h"
/**
 * Loads task data from disk into memory
 * @return: true if successful, false otherwise
 */
bool loadDataFromDisk(void) {
    FILE* file = fopen(STORAGE_FILENAME, "r");
    if (!file) {
        printf("No saved data found, starting with empty task list.\n");
        return true; /* Not an error - just no existing data */
    }
    
    taskCount = 0;
    char description[MAX_DESCRIPTION_LENGTH];
    char date[MAX_DATE_LENGTH];
    
    while (taskCount < MAX_TASKS) {
        /* Read description line */
        if (!fgets(description, sizeof(description), file)) {
            break; /* End of file or error */
        }
        
        /* Remove trailing newline from description */
        description[strcspn(description, "\n")] = '\0';
        
        /* Read date line */
        if (!fgets(date, sizeof(date), file)) {
            fprintf(stderr, "Warning: Incomplete task data found, skipping.\n");
            break;
        }
        
        /* Remove trailing newline from date */
        date[strcspn(date, "\n")] = '\0';
        
        /* Validate data before storing */
        if (strlen(description) == 0 || strlen(date) != 10) {
            fprintf(stderr, "Warning: Invalid task data found, skipping.\n");
            continue;
        }
        
        /* Store the task */
        strncpy(tasks[taskCount].description, description, MAX_DESCRIPTION_LENGTH - 1);
        tasks[taskCount].description[MAX_DESCRIPTION_LENGTH - 1] = '\0';
        
        strncpy(tasks[taskCount].date, date, MAX_DATE_LENGTH - 1);
        tasks[taskCount].date[MAX_DATE_LENGTH - 1] = '\0';
        
        taskCount++;
    }
    
    fclose(file);
    printf("Successfully loaded %d tasks from disk.\n", taskCount);
    return true;
}
/**
 * Saves task data from memory to disk
 * @return: true if successful, false otherwise
 */
bool saveDataToDisk(void) {
    FILE* file = fopen(STORAGE_FILENAME, "w");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file for saving tasks.\n");
        return false;
    }
    
    for (int i = 0; i < taskCount; i++) {
        if (fprintf(file, "%s\n%s\n", tasks[i].description, tasks[i].date) < 0) {
            fprintf(stderr, "Error: Failed to write task %d to file.\n", i);
            fclose(file);
            return false;
        }
    }
    
    if (fclose(file) != 0) {
        fprintf(stderr, "Error: Failed to close file properly.\n");
        return false;
    }
    
    printf("Successfully saved %d tasks to disk.\n", taskCount);
    return true;
}
