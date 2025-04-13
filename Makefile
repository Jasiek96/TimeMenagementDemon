# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
TESTS_DIR := tests

# Program name
PROGRAM_NAME_MAN := testDateTimeManual
PROGRAM_NAME_AUT := testDateTimeAuto
TARGET_MAN := $(BIN_DIR)/$(PROGRAM_NAME_MAN)
TARGET_AUT := $(BIN_DIR)/$(PROGRAM_NAME_AUT)

# Source and object files for main program
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Source and object files for manual tests
TESTS_MAN_SRCS := $(wildcard $(TESTS_DIR)/manual/*.cpp)
TESTS_MAN_OBJS := $(patsubst $(TESTS_DIR)/manual/%.cpp, $(OBJ_DIR)/%.o, $(TESTS_MAN_SRCS))

# Source and object files for automatic tests
TESTS_AUT_SRCS := $(wildcard $(TESTS_DIR)/auto/*.cpp)
TESTS_AUT_OBJS := $(patsubst $(TESTS_DIR)/auto/%.cpp, $(OBJ_DIR)/%.o, $(TESTS_AUT_SRCS))

# Debugging output
$(info Source files: $(SRCS))
$(info Object files: $(OBJS))
$(info Target: $(TARGET_MAN))
$(info Target: $(TARGET_AUT))

# Default target
all: $(TARGET_MAN) $(TARGET_AUT)

# Target to compile and run manual tests
testDTmanual: $(TARGET_MAN)
	@echo "Running manual tests: $(TARGET_MAN)..."
	@./$(TARGET_MAN)

# Target to compile and run automatic tests
testDTauto: $(TARGET_AUT)
	@echo "Running automatic tests: $(TARGET_AUT)..."
	@./$(TARGET_AUT)

# Link object files to create the manual test executable
$(TARGET_MAN): $(OBJS) $(TESTS_MAN_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Link object files to create the automatic test executable
$(TARGET_AUT): $(OBJS) $(TESTS_AUT_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile manual test files to object files
$(OBJ_DIR)/%.o: $(TESTS_DIR)/manual/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile automatic test files to object files
$(OBJ_DIR)/%.o: $(TESTS_DIR)/auto/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean testDTman testDTaut
