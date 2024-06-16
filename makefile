# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -std=c++11 -Wall -fPIC

# Directories
SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
BIN_DIR := bin
TEST_DIR := test
BENCHMARK_DIR := benchmark

# Source files
# List your source files here
SRC := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
# Generates .o files in the build directory
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Output library names
# Adjust these according to your needs
LIB_NAME := aesimp
STATIC_LIB := $(LIB_DIR)/lib$(LIB_NAME).a
SHARED_LIB := $(LIB_DIR)/lib$(LIB_NAME).so

# Test executables
# List all test files and benchmark files
TEST_SRC := $(wildcard $(TEST_DIR)/*.cpp)
TEST_BIN := $(TEST_SRC:$(TEST_DIR)/%.cpp=$(BIN_DIR)/%)
BENCHMARK_SRC := $(wildcard $(BENCHMARK_DIR)/*.cpp)
BENCHMARK_BIN := $(BENCHMARK_SRC:$(BENCHMARK_DIR)/%.cpp=$(BIN_DIR)/%)

# Default target
all: $(STATIC_LIB) $(SHARED_LIB) test_binaries

# Static library target
$(STATIC_LIB): $(OBJ) | $(LIB_DIR)
	ar rcs $@ $^

# Shared library target
$(SHARED_LIB): $(OBJ) | $(LIB_DIR)
	$(CXX) -shared -o $@ $^

# Object files compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile test and benchmark executables
test_binaries: $(TEST_BIN) $(BENCHMARK_BIN) | $(BIN_DIR)

# Rule to compile test files
$(BIN_DIR)/%: $(TEST_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(STATIC_LIB)

# Rule to compile benchmark files
$(BIN_DIR)/%: $(BENCHMARK_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $< $(STATIC_LIB)

# Create lib directory if it doesn't exist
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Test target
test: test_binaries
	@echo "Running tests..."
	@for test_file in $(BIN_DIR)/*test*; do \
		echo "Running $$test_file"; \
		$$test_file; \
	done

# Clean target
clean:
	rm -rf $(BUILD_DIR)/*.o $(LIB_DIR)/*.a $(LIB_DIR)/*.so $(BIN_DIR)/*

# Phony targets
.PHONY: all test_binaries test clean

