/**
 * Task Manager Application
 * Author: Jaden Mardini
 *  
 * 
 * Professional task management system demonstrating:
 * - Modular C programming
 * - Input validation and error handling
 * - File I/O operations
 * - Memory management
 * - Cross-platform compatibility
 */
#include <stdio.h>
#include <stdlib.h>
#include "../taskManagerOperations/taskManagerOperations.h"
#include "../taskDisplayManager/taskDisplayManager.h"
#include "../taskStorageHandler/taskStorageHandler.h"
/* Cross-platform screen clearing */
static void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
/* Display main menu with current status */
static void displayMenu(void) {
    printf("\n=== Task Manager ===\n");
    printf("Current tasks: %d/%d\n\n", taskCount, MAX_TASKS);
    printf("1. Add new task\n");
    printf("2. Delete task\n");
    printf("3. Update task\n");
    printf("4. Display single task\n");
    printf("5. Display tasks in range\n");
    printf("6. Display all tasks\n");
    printf("7. Search tasks\n");
    printf("8. Save and Exit\n");
    printf("\nEnter your choice: ");
}
/* Wait for user input before continuing */
static void waitForUser(void) {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n');
}
/* Handle menu operations with proper error checking */
static void handleMenuChoice(int choice) {
    clearScreen();
    
    switch (choice) {
        case 1:
            printf("\n=== Add New Task ===\n");
            addTask();
            break;
        case 2:
            printf("\n=== Delete Task ===\n");
            deleteTask();
            break;
        case 3:
            printf("\n=== Update Task ===\n");
            updateTask();
            break;
        case 4:
            printf("\n=== Display Single Task ===\n");
            displaySingleTask();
            break;
        case 5:
            printf("\n=== Display Tasks in Range ===\n");
            displayTasksInRange();
            break;
        case 6:
            printf("\n=== Display All Tasks ===\n");
            displayAllTasks();
            break;
        case 7:
            printf("\n=== Search Tasks ===\n");
            searchTasks();
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    if (choice != 8) waitForUser();
}
int main(void) {
    int choice;
    
    printf("=== Task Manager Application ===\n");
    printf("Loading saved tasks...\n");
    
    loadDataFromDisk();
    
    do {
        clearScreen();
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); /* Clear input buffer */
            waitForUser();
            continue;
        }
        while (getchar() != '\n'); /* Clear input buffer */
        
        if (choice >= 1 && choice <= 7) {
            handleMenuChoice(choice);
        } else if (choice == 8) {
            clearScreen();
            printf("\n=== Save and Exit ===\n");
            saveDataToDisk();
            printf("Thank you for using Task Manager!\n");
        } else {
            printf("Please enter a number between 1 and 8.\n");
            waitForUser();
        }
        
    } while (choice != 8);
    
    return EXIT_SUCCESS;
}
