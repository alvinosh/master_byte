CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99 -g
SRCDIR = ./src
BUILDDIR = ./build

# List all the source files with .c extension in the src directory
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Generate a list of object files by replacing .c with .o in the source file list
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

# Name of the final executable
EXECUTABLE = $(BUILDDIR)/main

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: remove all object files and the executable
clean:
	rm -f $(BUILDDIR)/*.o $(EXECUTABLE)