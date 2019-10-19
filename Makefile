CC := g++
FLAGS := -std=c++2a -w -g -pthread
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TEST_DIR := test
INCLUDE := -I./$(INC_DIR) 
TEST_LIBRARY := -lgtest -lgtest_main

# DEST := test
SOURCE_FILES=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(patsubst $(SOURCE_FILES)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

$(DEST): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ $(TEST_LIBRARY)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

# CC := g++
# FLAGS := -std=c++11 -w
# INC_DIR := include
# SRC_DIR := src
# BUILD_DIR := build
# BIN_DIR := bin
# DATA_DIR := data
# INCLUDE := -I./$(INC_DIR)

# $(BIN_DIR)/main: $(BUILD_DIR)/User.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/main.o
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ 

# $(BUILD_DIR)/main.o: main/main.cpp 
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

# $(BUILD_DIR)/Meeting.o: $(SRC_DIR)/Meeting.cpp $(INC_DIR)/Meeting.hpp $(INC_DIR)/Date.hpp
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<	

# $(BUILD_DIR)/Storage.o: $(SRC_DIR)/Storage.cpp $(INC_DIR)/Storage.hpp $(INC_DIR)/Path.hpp $(INC_DIR)/User.hpp $(INC_DIR)/Meeting.hpp
# 	@mkdir -p $(BUILD_DIR) $(DATA_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<	

# $(BUILD_DIR)/AgendaService.o: $(SRC_DIR)/AgendaService.cpp $(INC_DIR)/AgendaService.hpp $(INC_DIR)/Storage.hpp
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<	

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

# clean:
# 	@rm -rf $(BUILD_DIR)
# 	@rm -rf $(BIN_DIR)
# 	@rm -rf $(DATA_DIR)
