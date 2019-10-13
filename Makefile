CC := g++
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/User.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ 

$(BUILD_DIR)/main.o: main/main.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

$(BUILD_DIR)/Meeting.o: $(SRC_DIR)/Meeting.cpp $(INC_DIR)/Meeting.hpp $(INC_DIR)/Date.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<	

$(BUILD_DIR)/Storage.o: $(SRC_DIR)/Storage.cpp $(INC_DIR)/Storage.hpp $(INC_DIR)/Path.hpp $(INC_DIR)/User.hpp $(INC_DIR)/Meeting.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<	

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)