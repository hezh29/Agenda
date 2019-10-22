CC := g++
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DATA_DIR := data
DEPEND_DIR := dependence
INCLUDE := -I./$(INC_DIR)
vpath %.hpp $(INC_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.o $(BUILD_DIR)
vpath Agenda $(BIN_DIR)
sources:=$(wildcard $(SRC_DIR)/*.cpp)
objects:=$(sources:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
dependence:=$(sources:$(SRC_DIR)/%.cpp=$(DEPEND_DIR)/%.d)
start: Mkdir Agenda
Agenda: $(objects)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $(BIN_DIR)/$@ 
%.o:
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<
-include $(dependence)
$(DEPEND_DIR)/%.d: %.cpp 
	@mkdir -p $(DEPEND_DIR); \
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< $(INCLUDE) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
.PHONY: clean start Mkdir
clean:
	@rm -rf $(BUILD_DIR) $(DATA_DIR) $(BIN_DIR) $(DEPEND_DIR) 
Mkdir:
	@mkdir -p $(BUILD_DIR) $(DATA_DIR) $(BIN_DIR)


