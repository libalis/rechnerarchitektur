.PHONY: all clean jacobi

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

BX := -DBX=768
BY := -DBY=50

all: jacobi

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

jacobi: $(BIN_PATH)/jacobi

$(BIN_PATH)/jacobi: $(BUILD_PATH)/main.o $(BUILD_PATH)/draw.o $(BUILD_PATH)/jacobi.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/jacobi.o: $(SRC_PATH)/jacobi.c
	mkdir -p $(dir $@)
	$(CC) $(BX) $(BY) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
