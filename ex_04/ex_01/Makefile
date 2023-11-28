.PHONY: all clean jacobi jacobi_2

ROOT_PATH  := .
SRC_PATH   := $(ROOT_PATH)/src
BUILD_PATH := $(ROOT_PATH)/build
BIN_PATH   := $(ROOT_PATH)/bin

INC_PATH  := $(SRC_PATH)/include
INC_DIRS  := $(sort $(shell find $(INC_PATH) -type d))
INC_FLAGS := $(addprefix -iquote ,$(INC_DIRS))

CC      := icc
CFLAGS  := -Wall -pedantic -Werror -std=c99 -O3

LDFLAGS :=

CFLAGS_LIKWID := -I/apps/likwid/5.3.0/include -DLIKWID_PERFMON
LDFLAGS_LIKWID := -pthread -L/apps/likwid/5.3.0/lib/ -llikwid

all: jacobi jacobi_2

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

jacobi: $(BIN_PATH)/jacobi
jacobi_2: $(BIN_PATH)/jacobi_2

$(BIN_PATH)/jacobi: $(BUILD_PATH)/main.o $(BUILD_PATH)/draw.o $(BUILD_PATH)/jacobi.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS_LIKWID) $^ -o $@ $(LDFLAGS) $(LDFLAGS_LIKWID)

$(BIN_PATH)/jacobi_2: $(BUILD_PATH)/main.o $(BUILD_PATH)/draw.o $(BUILD_PATH)/jacobi_2.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS_LIKWID) $^ -o $@ $(LDFLAGS) $(LDFLAGS_LIKWID)

$(BUILD_PATH)/jacobi_2.o: $(SRC_PATH)/jacobi.c
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=2 $(INC_FLAGS) $(CFLAGS) $(CFLAGS_LIKWID) -MMD -MP -c $< -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) $(CFLAGS_LIKWID) -MMD -MP -c $< -o $@
