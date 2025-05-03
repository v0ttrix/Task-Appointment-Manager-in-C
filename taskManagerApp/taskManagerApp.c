//Jaden Mardini - PROG71990 - f24 - sec1 - GROUP #2

/*1. Open the Project:

  2. Double-click the .sln file to open the project in Visual Studio.
     Build the Project:
  
  3.Go to Build > Build Solution (or press Ctrl+Shift+B).
    
  4. Press F5 to run the project in Debug mode.
 
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Choose from the following features>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Add a Task:
Choose "1" from the menu.
Enter the task description and date when prompted.
Delete a Task:
Choose "2" and provide the ID of the task you want to delete.
Update a Task:
Choose "3" to modify an existing task’s description or date.
View a Task:
Choose "4" to display the details of a specific task by ID.
Search Tasks:
Choose "7" and input a keyword to find matching tasks.
Save and Exit:
Choose "8" to save all changes and exit the app safely.

*/

#include <stdio.h> // standard i/o functions like printf, scanf
#include <stdlib.h> // for system calls like system("cls")
#include "../taskManagerOperations/taskManagerOperations.h" // handles task-related operations
#include "../taskDisplayManager/taskDisplayManager.h" // handles displaying tasks in different ways
#include "../taskStorageHandler/taskStorageHandler.h" // for loading/saving tasks to/from disk
#include "../taskStorageHandler/taskStorageHandler.c" // directly includes the implementation (not ideal but works for now)

static void clearScreen()
{
    // this function clears the console screen
#ifdef _WIN32 // windows-specific screen clearing
    system("cls");
#else // for unix-like systems (linux/mac)
    system("clear");
#endif
}

static void addTaskMenu()
{
    clearScreen(); // clears the screen before showing the menu
    printf("\n--- Add New Task ---\n"); // header for the add task menu
    addTask(); // calls the addTask function to handle user input for adding a task
    printf("\nPress Enter to return to the main menu..."); // prompt to let user pause before returning
    (void)getchar(); // waits for user to press enter
}

static void deleteTaskMenu()
{
    clearScreen(); // clears the screen before showing the menu
    printf("\n--- Delete Task ---\n"); // header for the delete task menu
    deleteTask(); // calls the deleteTask function to handle task deletion
    printf("\nPress Enter to return to the main menu..."); // prompt to pause before returning
    (void)getchar(); // waits for user to press enter
}

static void updateTaskMenu()
{
    clearScreen(); // clears the screen
    printf("\n--- Update Task ---\n"); // header for the update task menu
    updateTask(); // calls the updateTask function to modify a task
    printf("\nPress Enter to return to the main menu..."); // lets user pause
    (void)getchar(); // waits for enter
}

static void displaySingleTaskMenu()
{
    clearScreen(); // clears the screen
    printf("\n--- Display Single Task ---\n"); // header for displaying a single task
    displaySingleTask(); // calls function to show details of one task
    printf("\nPress Enter to return to the main menu..."); // pause prompt
    (void)getchar(); // waits for enter
}

static void displayTasksInRangeMenu()
{
    clearScreen(); // clears the screen
    printf("\n--- Display Tasks in Range ---\n"); // header for displaying tasks within a date range
    displayTasksInRange(); // calls function to display tasks within the given range
    printf("\nPress Enter to return to the main menu..."); // pause prompt
    (void)getchar(); // waits for enter
}

static void displayAllTasksMenu()
{
    clearScreen(); // clears the screen
    printf("\n--- Display All Tasks ---\n"); // header for displaying all tasks
    displayAllTasks(); // calls function to display all stored tasks
    printf("\nPress Enter to return to the main menu..."); // pause prompt
    (void)getchar(); // waits for enter
}

static void searchTasksMenu() {
    clearScreen(); // clears the screen
    printf("\n--- Search Tasks ---\n"); // header for searching tasks
    searchTasks(); // calls function to search tasks based on user input
    printf("\nPress Enter to return to the main menu..."); // pause prompt
    (void)getchar(); // waits for enter
}

int main()
{
    int choice; // stores the user's menu choice

    loadDataFromDisk();  // loads saved tasks from disk into memory

    while (1) { // infinite loop to keep showing the menu until the user exits
        clearScreen(); // clears the screen
        printf("\nTask Manager Menu\n"); // main menu header
        printf("1. Add new task\n"); // menu option to add a task
        printf("2. Delete task\n"); // menu option to delete a task
        printf("3. Update task\n"); // menu option to update a task
        printf("4. Display single task\n"); // option to view details of one task
        printf("5. Display tasks in range\n"); // option to view tasks within a date range
        printf("6. Display all tasks\n"); // option to view all tasks
        printf("7. Search tasks\n"); // option to search tasks
        printf("8. Save and Exit\n"); // option to save and exit the program
        printf("Enter your choice: "); // prompt for user to enter their menu choice
        scanf_s("%d", &choice); // reads user input for menu choice
        (void)getchar(); // consumes the newline character left by scanf_s

        switch (choice) { // handles the user's choice
        case 1:
            addTaskMenu(); // call the menu for adding a task
            break;
        case 2:
            deleteTaskMenu(); // call the menu for deleting a task
            break;
        case 3:
            updateTaskMenu(); // call the menu for updating a task
            break;
        case 4:
            displaySingleTaskMenu(); // call the menu for viewing one task
            break;
        case 5:
            displayTasksInRangeMenu(); // call the menu for viewing tasks in a range
            break;
        case 6:
            displayAllTasksMenu(); // call the menu for viewing all tasks
            break;
        case 7:
            searchTasksMenu(); // call the menu for searching tasks
            break;
        case 8:
            saveDataToDisk(); // save all tasks to disk
            printf("\nTasks saved successfully. Exiting...\n"); // confirm save
            return 0; // exit the program
        default:
            printf("\nInvalid choice. Press Enter to try again..."); // prompt for invalid input
            (void)getchar(); // waits for enter
        }
    }
}
