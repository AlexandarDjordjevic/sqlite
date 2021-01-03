
MAIN_SRC = main.c 
SRC_DIR = source
TEST_HEADER_SRC = $(wildcard tests/*.cpp)
LDFLAGS += -L$(LIB_DIR)/ -lsqlite
CXXFLAGS += -std=c++11 -Iinclude -fPIC

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TESTS_DIR = $(BUILD_DIR)/tests
LIB_DIR = $(BUILD_DIR)/lib
BIN_DIR = $(BUILD_DIR)/bin

MODULES := $(notdir $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS := $(MODULES:.cpp=.o)

.PHONY: all
all: lsqlite main unit_tests

%.o: $(SRC_DIR)/%.cpp
	$(info Building $<)
	$(CXX) -c $(CXXFLAGS) -Iinclude $(LDFLAGS) -o $(OBJ_DIR)/$@ $<

.PHONY: objects 
objects: make_dirs $(OBJECTS)

.PHONY: lsqlite
lsqlite: make_dirs objects
	$(info Creating Library)
	ar rDc $(LIB_DIR)/libsqlite.a $(wildcard $(OBJ_DIR)/*.o)
	ranlib $(LIB_DIR)/libsqlite.a

#Tests
.PHONY: unit_tests
unit_tests: lsqlite 
	$(CXX) $(TEST_HEADER_SRC) $ $(CXXFLAGS) $(LDFLAGS) -lgtest -lgtest_main -lpthread -o $(TESTS_DIR)/$@

.PHONY: run_tests
run_tests: unit_tests
	clear
	./$(TESTS_DIR)/$<


#prepare all directories for build artifacts
make_dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(TESTS_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(BIN_DIR)

.PHONY: main
main: lsqlite
	$(CXX) $(MAIN_SRC) $ $(CXXFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main

.PHONY: run_main
run_main:
	clear
	./$(BIN_DIR)/main $(shell pwd)/"College.db"

.PHONY: clean
clean:
	rm -fr $(BUILD_DIR)