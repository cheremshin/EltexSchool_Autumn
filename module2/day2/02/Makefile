CC = gcc
FLAGS = -g -std=c11 -Werror
INC_DIR = -L. -Iinclude

TARGET = program

SRC_DIR = src
TARGET_DIR = build
OBJ_DIR = $(TARGET_DIR)/obj

SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))


all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(FLAGS) $(INC_DIR) $^ -o $(TARGET_DIR)/$@ -lm

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(TARGET_DIR)
