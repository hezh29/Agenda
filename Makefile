CC := g++
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/User.o $(BUILD_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ 

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.hpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
	@em -rf $(BIN_DIR)