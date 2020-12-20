
SRC = main.c source/helpers.c source/sqlite.c
INC = -Iinclude
FLAGS += -std=c99
BIN = application
OUT_DIR = build

.PHONY: all
all: prepare_OUT_DIR
	$(CC) $(SRC) $(FLAGS) $(INC) -o $(OUT_DIR)/$(BIN)

.PHONY: run
run: all
	./$(OUT_DIR)/$(BIN)

prepare_OUT_DIR:
	mkdir -p $(OUT_DIR)

.PHONY: clean
clean:
	rm -fr $(OUT_DIR)