#!/bin/bash

echo "Fixing Task Manager Project..."

# Fix main app - replace scanf_s with scanf
sed -i 's/scanf_s/scanf/g' taskManagerApp/taskManagerApp.c

# Remove problematic direct .c include
sed -i '/taskStorageHandler\.c/d' taskManagerApp/taskManagerApp.c

# Fix taskManagerOperations.c - remove problematic includes
sed -i '/pch\.h/d' taskManagerOperations/taskManagerOperations.c
sed -i '/taskManagerOperations\.c/d' taskStorageHandler/taskStorageHandler.c

# Fix scanf_s in taskManagerOperations.c
sed -i 's/scanf_s/scanf/g' taskManagerOperations/taskManagerOperations.c

# Add missing includes where needed
sed -i '1i#include <stdbool.h>' taskManagerOperations/taskManagerOperations.c
sed -i '1i#include <stdbool.h>' taskStorageHandler/taskStorageHandler.c

echo "Building project..."
make clean
make

if [ $? -eq 0 ]; then
    echo "Project fixed and built successfully!"
    echo "Run ./task_manager to start the application"
else
    echo "Build failed. Checking for remaining issues..."
fi
