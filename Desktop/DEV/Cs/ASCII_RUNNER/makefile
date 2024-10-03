# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -I.

# Source files
SRC = actions.c cells.c debug.c main.c print.c tools.c

# Object files
OBJ = $(SRC:.c=.o)

# Headers
HEADERS = _ascii.h _header.h

# Executable name
EXEC = my_program

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

nf: CFLAGS =
nf: $(EXEC)

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean
