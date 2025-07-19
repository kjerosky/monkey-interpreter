TARGET = $(EXEC_DIR)/monkey-interpreter
CC := g++
CC_FLAGS = --std=c++17 -Wall -MMD -MP -I $(SRC_DIR)

SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/objs
EXEC_DIR := $(BUILD_DIR)/executable

# Source files for the main executable (include main.cpp)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Source files for test executables (exclude main.cpp)
TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
SRC_NO_MAIN := $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))
TEST_NAMES := $(notdir $(basename $(TEST_SRCS)))
TEST_TARGETS := $(addprefix $(EXEC_DIR)/, $(TEST_NAMES))

DEPS := $(OBJS:.o=.d)

all: $(TARGET) $(TEST_TARGETS)

# Main program
$(TARGET): $(OBJS) | $(EXEC_DIR)
	$(CC) -o $@ $(OBJS) $(CC_FLAGS)

# Object files for src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) -o $@ -c $< $(CC_FLAGS)

# Test targets
$(EXEC_DIR)/%: $(TEST_DIR)/%.cpp $(SRC_NO_MAIN) | $(EXEC_DIR)
	$(CC) -o $@ $< $(SRC_NO_MAIN) $(CC_FLAGS)

# Create necessary directories
$(EXEC_DIR) $(OBJ_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
