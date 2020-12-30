
SRC = main.c source/helpers.c source/Database.cpp
INC = -Iinclude
FLAGS += -std=c++11
BIN = application
OUT_DIR = build

.PHONY: all
all: prepare_OUT_DIR
	$(CXX) $(SRC) $(FLAGS) $(INC) -o $(OUT_DIR)/$(BIN)

.PHONY: run
run: all
	./$(OUT_DIR)/$(BIN) $(PWD)/College.db

prepare_OUT_DIR:
	mkdir -p $(OUT_DIR)

.PHONY: clean
clean:
	rm -fr $(OUT_DIR)