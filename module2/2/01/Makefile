CC = gcc
FLAGS = -g -std=c11 -Werror
TEST_FLAGS = -lcheck -lsubunit -lpthread -lrt -lm
INC_DIR = -L. -Iinclude

TARGET = program
TEST_TARGET = test

SRC_DIR = src
TEST_SRC_DIR = tests
TARGET_DIR = build
OBJ_DIR = $(TARGET_DIR)/obj
TEST_OBJ_DIR = $(TARGET_DIR)/test_obj

RAW_SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")
SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(RAW_SRC_FILES))
TEST_SRC_FILES = $(shell find $(TEST_SRC_DIR) -type f -name "*.c")

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_SRC_DIR)/%.c, $(TEST_OBJ_DIR)/%.o, $(TEST_SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(OBJ_DIR)/main.o
	$(CC) $(FLAGS) $(INC_DIR) $^ -o $(TARGET_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC_DIR) -c $^ -o $@

$(TEST_TARGET): $(TEST_OBJ_FILES) $(OBJ_FILES)
	$(CC) $(FLAGS) $(INC_DIR) $^ -o $(TARGET_DIR)/$@ $(TEST_FLAGS)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC_DIR) -c $^ -o $@

clean:
	rm -rf $(TARGET_DIR)

leaks: $(TEST_TARGET)
	@valgrind --leak-check=full --show-leak-kinds=all $(TARGET_DIR)/$(TEST_TARGET)
