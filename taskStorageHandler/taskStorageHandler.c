//YashB - PROG71990 - Fall2024 - Group 2 - Project

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "taskStorageHandler.h"//header for storage functions
#include "../taskManagerOperations/taskManagerOperations.h" //header for task manager operations
#include "../taskManagerOperations/taskManagerOperations.c"//header for including implementation of task manager operations 

extern int taskCount;   //track number of tasks
extern Task tasks[MAX_TASKS];  //array of tasks

void loadDataFromDisk() 
{
    FILE* file = fopen("tasks.dat", "r");       //open file
    if (file) 
    {
        while (fscanf_s(file, "%99[^\n]\n%10s\n", tasks[taskCount].description, (unsigned int)sizeof(tasks[taskCount].description), tasks[taskCount].date, (unsigned int)sizeof(tasks[taskCount].date)) == 2)
        {
            taskCount++;
            if (taskCount >= MAX_TASKS) break;  //to prevent exceeding the maximum amount of tasks
        }
        fclose(file);       // close file once done reading
        printf("Tasks loaded successfully.\n");
    }
    else {  //for cases where file doesn't exist
        printf("No saved data found, starting fresh.\n");
    }
}

void saveDataToDisk()
{
    FILE* file = fopen("tasks.dat", "w");   //open file for writing
    if (file) 
    {
        for (int i = 0; i < taskCount; i++)
        {
            fprintf(file, "%s\n%s\n", tasks[i].description, tasks[i].date);
        }
        fclose(file);       //close file and save successfully
        printf("Tasks saved successfully.\n");
    }
    else 
    {
        printf("Error saving data.\n");     //to handle cases where file cant be saved
    }
}
