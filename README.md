# Task Appointment Manager in C
## Overview
A comprehensive task management system written in C with persistent storage, input validation, and user-friendly interface.
## Authors
- 
- 
- 
## Features
- Add, delete, and update tasks
- Display single tasks or all tasks
- Filter tasks by date range
- Search tasks by keyword
- Persistent storage to disk
- Input validation and error handling
- Cross-platform compatibility
## Building the Project
### Using Make (Recommended)
```bash
make
./task_manager
```
### Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -g -o task_manager \
    taskManagerApp/taskManagerApp.c \
    taskManagerOperations/taskManagerOperations.c \
    taskStorageHandler/taskStorageHandler.c \
    taskUtilities/taskUtilities.c \
    taskDisplayManager/taskDisplayManager.c
```
## Usage
1. Run the executable
2. Choose from the menu options (1-8)
3. Follow the prompts for each operation
4. Use option 8 to save and exit
## Code Improvements Made
- Proper header guards and documentation
- Input validation and error handling
- Memory safety improvements
- Consistent coding style
- Modular design with clear separation of concerns
- Cross-platform compatibility
- Better user experience with formatted output
