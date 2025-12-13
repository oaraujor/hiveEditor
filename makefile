CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lncurses
SRC_DIR = src
BUILD_DIR = build
INC_DIR = include
LOG_DIR = logs
OUT_TXT = out_txt
LOG_FILE = $(LOG_DIR)/hive_mem_logs.txt
TARGET = $(BUILD_DIR)/hiveEditor
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	@echo "LINKING!\n"
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "CREATING .O FILES\n"
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(LOG_DIR)
	@mkdir -p $(OUT_TXT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "CLEANING BIN-LOGS-TXT-TEST"
	$(RM) -rf $(BUILD_DIR)/*
	$(RM) -rf $(LOG_DIR)/*
	$(RM) -rf $(OUT_TXT)/

run:
	$(TARGET)
	@wc $(OUT_TXT)/*.txt

memtest:
	@echo "CHECKING FOR MEMORY LEAKS | $(TARGET)\n"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --vgdb=full --log-file=$(LOG_FILE) -s $(TARGET)
	@echo "\nLOGS SAVED | $(LOG_FILE)"

show-vlogs:
	@cat $(LOG_FILE)

.PHONY: clean run memtest show-vlogs
