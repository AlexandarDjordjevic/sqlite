PRONY: all

SRC += main.c source/helpers.c source/sqldriver.c
FLAGS += -std=c99
BIN = application
OUT_DIR = build

.PHONY: all
all: prepare_OUT_DIR
	${CC} ${SRC} ${FLAGS} -o ${OUT_DIR}/${BIN}

.PHONY: run
run: all
	./${OUT_DIR}/${BIN}

prepare_OUT_DIR:
	mkdir -p ${OUT_DIR}

.PHONY: clean
clean:
	rm -fr ${OUT_DIR}