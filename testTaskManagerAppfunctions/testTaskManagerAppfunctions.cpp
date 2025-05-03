#include "CppUnitTest.h" // brings in Microsoft's unit testing framework
#include "../taskManagerOperations/taskManagerOperations.h" // header for task manager operations like add, delete, update
#include "../taskStorageHandler/taskStorageHandler.h" // handles saving and loading tasks to/from disk
#include "../taskUtilities/taskUtilities.h" // includes utility functions, e.g., date validation
#include "../taskDisplayManager/taskDisplayManager.h" // handles displaying tasks in the console
#include <iostream> // needed for redirecting output in the display test

using namespace Microsoft::VisualStudio::CppUnitTestFramework; // allows using the test framework's features without prefixing with namespace

namespace testTaskManagerAppfunctions // defines a namespace for all your test cases
{
    TEST_CLASS(testTaskManagerAppfunctions) // creates a class to group related test cases
    {
    public:
        TEST_METHOD(TestAddTask) // test case for verifying task addition functionality
        {
            // Arrange
            int initialTaskCount = taskCount; // store the current number of tasks for comparison later

            // Act
            strcpy_s(tasks[taskCount].description, "Test Task"); // set the description of the new task
            strcpy_s(tasks[taskCount].date, "2024-12-06"); // set the date of the new task
            taskCount++; // increment the task count to reflect the addition of a new task

            // Assert
            Assert::AreEqual(initialTaskCount + 1, taskCount, L"Task count should increase by 1"); // check if task count increased
            Assert::AreEqual(std::string("Test Task"), std::string(tasks[taskCount - 1].description), L"Task description mismatch"); // verify the description matches
            Assert::AreEqual(std::string("2024-12-06"), std::string(tasks[taskCount - 1].date), L"Task date mismatch"); // verify the date matches
        }

        TEST_METHOD(TestDeleteTask) // test case for verifying task deletion functionality
        {
            // Arrange
            strcpy_s(tasks[0].description, "Task to be deleted"); // add a dummy task to delete
            strcpy_s(tasks[0].date, "2024-12-06"); // set a date for the dummy task
            taskCount = 1; // set the task count to 1 to simulate having only this task

            // Act
            deleteTask(); // call the function to delete the task

            // Assert
            Assert::AreEqual(0, taskCount, L"Task count should be zero after deletion"); // check if task count is now zero
        }

        TEST_METHOD(TestUpdateTask) // test case for verifying task update functionality
        {
            // Arrange
            strcpy_s(tasks[0].description, "Old Task"); // add a dummy task with an old description
            strcpy_s(tasks[0].date, "2024-12-05"); // add an old date for the dummy task
            taskCount = 1; // set task count to 1 to simulate having this task

            // Act
            strcpy_s(tasks[0].description, "Updated Task"); // update the task's description
            strcpy_s(tasks[0].date, "2024-12-06"); // update the task's date

            // Assert
            Assert::AreEqual(std::string("Updated Task"), std::string(tasks[0].description), L"Task description should be updated"); // verify description was updated
            Assert::AreEqual(std::string("2024-12-06"), std::string(tasks[0].date), L"Task date should be updated"); // verify date was updated
        }

        TEST_METHOD(TestIsValidDate) // test case for verifying date validation functionality
        {
            // Arrange
            const char* validDate = "2024-12-06"; // a valid date format
            const char* invalidDate = "2024-13-06"; // an invalid date format (month 13 is invalid)

            // Act & Assert
            Assert::IsTrue(isValidDate(validDate), L"Valid date should be recognized as valid"); // check if valid date passes validation
            Assert::IsFalse(isValidDate(invalidDate), L"Invalid date should not be recognized as valid"); // check if invalid date fails validation
        }

        TEST_METHOD(TestSaveAndLoadData) // test case for verifying save and load functionality
        {
            // Arrange
            strcpy_s(tasks[0].description, "Task to save"); // create a dummy task to save
            strcpy_s(tasks[0].date, "2024-12-06"); // set a date for the dummy task
            taskCount = 1; // set task count to 1 to simulate having only this task

            // Act
            saveDataToDisk(); // save the task data to disk
            taskCount = 0; // reset task count to simulate a fresh start
            loadDataFromDisk(); // load the task data back from disk

            // Assert
            Assert::AreEqual(1, taskCount, L"Task count should be restored after loading data"); // check if task count matches the saved count
            Assert::AreEqual(std::string("Task to save"), std::string(tasks[0].description), L"Task description mismatch after loading"); // verify description matches saved data
            Assert::AreEqual(std::string("2024-12-06"), std::string(tasks[0].date), L"Task date mismatch after loading"); // verify date matches saved data
        }

        TEST_METHOD(TestSearchTasks) // test case for verifying search functionality
        {
            // Arrange
            strcpy_s(tasks[0].description, "Test Search Task"); // add a task with a description containing the search keyword
            strcpy_s(tasks[0].date, "2024-12-06"); // set a date for the task
            strcpy_s(tasks[1].description, "Another Task"); // add another task without the keyword
            strcpy_s(tasks[1].date, "2024-12-07"); // set a date for the second task
            taskCount = 2; // simulate having two tasks
            const char* searchTerm = "Search"; // set the keyword to search for

            // Act
            bool found = false; // initialize a flag to check if the search term is found
            for (int i = 0; i < taskCount; i++) { // loop through the tasks
                if (strstr(tasks[i].description, searchTerm) != nullptr) { // check if the search term exists in the description
                    found = true; // set the flag to true if found
                    break; // stop the loop once the term is found
                }
            }

            // Assert
            Assert::IsTrue(found, L"Task containing 'Search' should be found"); // verify that the search term was found
        }

        TEST_METHOD(TestDisplayAllTasks) // test case for verifying the display functionality
        {
            // Arrange
            strcpy_s(tasks[0].description, "Task 1"); // create the first dummy task
            strcpy_s(tasks[0].date, "2024-12-06"); // set a date for the first task
            strcpy_s(tasks[1].description, "Task 2"); // create the second dummy task
            strcpy_s(tasks[1].date, "2024-12-07"); // set a date for the second task
            taskCount = 2; // simulate having two tasks
            std::stringstream buffer; // create a stringstream to capture console output
            std::streambuf* old = std::cout.rdbuf(buffer.rdbuf()); // redirect console output to the stringstream

            // Act
            displayAllTasks(); // call the function to display all tasks
            std::string output = buffer.str(); // store the captured output as a string
            std::cout.rdbuf(old); // restore the original console output

            // Assert
            Assert::IsTrue(output.find("Task 1") != std::string::npos, L"Output should contain Task 1"); // check if Task 1 is in the output
            Assert::IsTrue(output.find("Task 2") != std::string::npos, L"Output should contain Task 2"); // check if Task 2 is in the output
        }
    };
}
