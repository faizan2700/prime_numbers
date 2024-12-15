# Specify the C++ compiler
CC = g++  # Just define the compiler here 
$(info Using compiler: $(CC))

# Specify compiler flags (optional) 
# CFLAGS = -Wall -Wextra -Werror -I./include -I../threading_lib -std=c++11
CFLAGS = -Wall -Wextra -Werror -I./include -I../threading_lib -std=c++17  # Add the relative include path

# Specify the build directory
BUILD_DIR = build

# Target: all (default)
all: $(BUILD_DIR)/main

# Target: $(BUILD_DIR)/main
$(BUILD_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/utils.o
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/main $(BUILD_DIR)/main.o $(BUILD_DIR)/utils.o

# Target: $(BUILD_DIR)/main.o
$(BUILD_DIR)/main.o: src/main.cpp include/header.h
	$(CC) $(CFLAGS) -c src/main.cpp -o $(BUILD_DIR)/main.o

# Target: $(BUILD_DIR)/utils.o
$(BUILD_DIR)/utils.o: src/utils.cpp include/header.h
	$(CC) $(CFLAGS) -c src/utils.cpp -o $(BUILD_DIR)/utils.o

# Target: clean
clean:
	rm -rf $(BUILD_DIR)/*

# Target: run
run: $(BUILD_DIR)/main
	$(BUILD_DIR)/main    # Run the executable from the build directory
