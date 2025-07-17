# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
#LDFLAGS = -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include

# Find all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Change their extension to .o and place in build/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Final binary
TARGET = $(BUILD_DIR)/hiveEditor

# Default target
all: $(TARGET)

# Rule to link objects into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile .c files to .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR)/*

# Run the editor
run: all
	$(TARGET)

.PHONY: all clean run
