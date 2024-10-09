
CC = gcc

#Directories

SRC_DIR = src
BUILD_DIR = build
LIB_DIR = 
INCLUDE_DIR = include
TEST_DIR = tests

#ouput location

TARGET = $(BUILD_DIR)/engine

#Test output
TEST_SRC = $(TEST_DIR)/sdl3_test.c
TEST_TARGET = $(BUILD_DIR)/sdl3_test


#Default flags
CFLAGS = -Iinclude -Wall -g
LDFLAGS =

# Platform detection
# The default is based on system detection, but users can override it by setting PLATFORM=<windows|linux|macos>
ifeq ($(PLATFORM),)
  ifeq ($(OS),Windows_NT)
    PLATFORM = windows
  else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
      PLATFORM = linux
    endif
    ifeq ($(UNAME_S),Darwin)
      PLATFORM = macos
    endif
  endif
endif


# Platform-specific flags for SDL2 and OpenGL  /nothing is tested
ifeq ($(PLATFORM),windows)
  CFLAGS += -DPLATFORM_WINDOWS -I/ucrt64/include/SDL3 -I/ucrt64/include/GL -I/ucrt64/include -I/include/ecs
  LDFLAGS = $(LDFLAGS_COMMON) -lSDL3 -lpng   

else ifeq ($(PLATFORM),linux)
  CFLAGS += -DPLATFORM_LINUX `sdl3-config --cflags`
  LDFLAGS = $(LDFLAGS_COMMON) `sdl3-config --libs` -lGL -lGLEW

else ifeq ($(PLATFORM),macos)
  CFLAGS += -DPLATFORM_MACOS -I/usr/local/include/SDL3
  LDFLAGS = $(LDFLAGS_COMMON) -L/usr/local/lib -lSDL3 -framework OpenGL -lGLEW
endif


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

# Subroutine for running tests
test: $(TEST_TARGET)
	@echo "Running Glew test..."
	./$(TEST_TARGET)

# Build the test file
$(TEST_TARGET): $(TEST_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -Iinclude/ecs $(SRC) $(TEST_SRC) -o $(TEST_TARGET) $(LDFLAGS) 

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
