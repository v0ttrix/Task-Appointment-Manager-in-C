CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = task_manager
SRCDIR = .
OBJDIR = obj

# Source files
SOURCES = taskManagerApp/taskManagerApp.c \
          taskManagerOperations/taskManagerOperations.c \
          taskStorageHandler/taskStorageHandler.c \
          taskUtilities/taskUtilities.c \
          taskDisplayManager/taskDisplayManager.c

# Object files
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Create object directory structure
$(shell mkdir -p $(OBJDIR)/taskManagerApp $(OBJDIR)/taskManagerOperations $(OBJDIR)/taskStorageHandler $(OBJDIR)/taskUtilities $(OBJDIR)/taskDisplayManager)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
