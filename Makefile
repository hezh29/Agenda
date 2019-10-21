# CC := g++
# FLAGS := -std=c++2a -w -g -pthread
# INC_DIR := include
# SRC_DIR := src
# BUILD_DIR := build
# BIN_DIR := bin
# TEST_DIR := test
# INCLUDE := -I./$(INC_DIR) 
# TEST_LIBRARY := -lgtest -lgtest_main

# # DEST := test
# SOURCE_FILES=$(shell find $(SRC_DIR) -name '*.cpp')
# OBJS=$(patsubst $(SOURCE_FILES)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCE_FILES))

# $(DEST): $(OBJS)
# 	@mkdir -p $(BIN_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ $(TEST_LIBRARY)

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	@mkdir -p $(BUILD_DIR)
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

CC := g++
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DATA_DIR := data
DEPEND_DIR := dependence
INCLUDE := -I./$(INC_DIR)
# Object := $(BUILD_DIR)/User.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o \
# 			$(BUILD_DIR)/Storage.o $(BUILD_DIR)/AgendaService.o \
# 			$(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Agenda.o 

vpath %.hpp $(INC_DIR)
vpath %.cpp $(SRC_DIR)
vpath %.o $(BUILD_DIR)

# $(BIN_DIR)/Agenda: $(Object)
# 	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ 

# $(BUILD_DIR)/%.o: %.cpp
# 	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<

# $(BUILD_DIR)/Agenda.o: AgendaUI.hpp 
# $(BUILD_DIR)/AgendaUI.o: AgendaUI.hpp AgendaService.hpp 
# $(BUILD_DIR)/Meeting.o: Meeting.hpp Date.hpp
# $(BUILD_DIR)/Storage.o: Storage.hpp Path.hpp User.hpp Meeting.hpp
# $(BUILD_DIR)/AgendaService.o: AgendaService.hpp Storage.hpp
# $(BUILD_DIR)/Date.o: Date.hpp
# $(BUILD_DIR)/User.o: User.hpp

#使用$(wildcard *.c)来获取工作目录下的所有.c文件的列表
sources:=$(wildcard $(SRC_DIR)/*.cpp)
objects:=$(sources:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
#这里,dependence是所有.d文件的列表.即把串sources串里的.c换成.d
dependence:=$(sources:$(SRC_DIR)/%.cpp=$(DEPEND_DIR)/%.d)
# start: Agenda
$(BIN_DIR)/Agenda: $(objects)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@ 
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR) $(DATA_DIR) $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<
include $(dependence) #注意该句要放在终极目标all的规则之后，否则.d文件里的规则会被误当作终极规则了
$(DEPEND_DIR)/%.d: %.cpp
	@mkdir -p $(DEPEND_DIR); \
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< $(INCLUDE) > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(BUILD_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean start
clean:
	@rm -rf $(BUILD_DIR) $(DATA_DIR) $(BIN_DIR) $(DEPEND_DIR) 
# .PHONY : clean Mkdir test

# Mkdir:
# 	@mkdir -p $(BUILD_DIR) $(DATA_DIR) $(BIN_DIR) $(DEPEND_DIR)

# clean:
# 	@rm -rf $(BUILD_DIR)/*
# 	@rm -rf $(BIN_DIR)/*
# 	@rm -rf $(DATA_DIR)/*



