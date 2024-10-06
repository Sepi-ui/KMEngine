
CC = gcc

#Directories

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = 
INCLUDE_DIR = include


#ouput location

TARGET = $(BUILD_DIR)/engine

#flags
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -lSDL2 -lSDL2main -lGL

#sources
SRC = $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

#Create Engine Binary
all: $(TARGET)

#build Binary
$(TARGET): $(OBJ)
	@echo "Linking Engine"
	$(CC) $(OBJ) -o$(TARGET) $(LDFLAGS)

#Compile source files

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< ..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#Cleanup

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)/*
	@echo "Cleaned up"

#run Engine

run: $(TARGET)
	@echo "Running Engine.."
	./$(TARGET)

#phony Targets
.PHONY: clean run
