CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -I./src

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

CORE_SRC := src/AES.cpp src/AES_CBC.cpp src/helper.cpp src/padding.cpp
CORE_OBJ := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(CORE_SRC))

AES_APP_SRC := test/test_ECB.cpp
TEST_APP_SRC := test/test_CBC.cpp
BENCH_APP_SRC := benchmark/benchmark_CBC.cpp

AES_APP := $(BIN_DIR)/aes
TEST_APP := $(BIN_DIR)/test_cbc
BENCH_APP := $(BIN_DIR)/benchmark_cbc

.PHONY: all clean test benchmark dirs

all: $(AES_APP) $(TEST_APP) $(BENCH_APP)

dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: src/%.cpp | dirs
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(AES_APP): $(AES_APP_SRC) $(CORE_OBJ) | dirs
	$(CXX) $(CXXFLAGS) $< $(CORE_OBJ) -o $@

$(TEST_APP): $(TEST_APP_SRC) $(CORE_OBJ) | dirs
	$(CXX) $(CXXFLAGS) $< $(CORE_OBJ) -o $@

$(BENCH_APP): $(BENCH_APP_SRC) $(CORE_OBJ) | dirs
	$(CXX) $(CXXFLAGS) $< $(CORE_OBJ) -o $@

test: $(TEST_APP)
	./$(TEST_APP)

benchmark: $(BENCH_APP)
	./$(BENCH_APP)

clean:
	rm -rf $(BUILD_DIR)
