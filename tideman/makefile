# Compiler and flags
CC= clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDLIBS = -lcrypt -lcs50 -lm

# Executable name
TARGET = tideman

# Source files
SRC = tideman.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDLIBS)

# Run the program with predefined arguments
run: $(TARGET)
	./$(TARGET) alice bob charlie

# Clean up build artifacts
clean:
	rm -f $(TARGET)

.PHONY: all run clean