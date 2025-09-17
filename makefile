CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lncurses

ARGS = test_file.txt

SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
TEST_DIR = test_main

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = $(BUILD_DIR)/hiveEditor
TARGET_TEST = $(BUILD_DIR)/hiveEditor_test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(BUILD_DIR)/*
	clear

run: all
	$(TARGET)

safety:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(TARGET) 

test:
	$(CC) $(CFLAGS) $(TEST_DIR)/test_main.c -o $(TARGET_TEST)

run_test:
	$(TARGET_TEST) $(ARGS)

safety_test:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s $(TARGET_TEST) $(ARGS)
.PHONY: all clean run safety test run_test safety_test
