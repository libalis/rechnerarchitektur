.PHONY: all clean stream

ROOT_PATH  := .
SRC_PATH   := $(ROOT_PATH)/src
BUILD_PATH := $(ROOT_PATH)/build
BIN_PATH   := $(ROOT_PATH)/bin

INC_PATH  := $(SRC_PATH)/include
INC_DIRS  := $(sort $(shell find $(INC_PATH) -type d))
INC_FLAGS := $(addprefix -iquote ,$(INC_DIRS))

CC      := icc
CFLAGS  := -Wall -pedantic -Werror -std=c11 -qopt-streaming-stores always -O3 -fopenmp

LDFLAGS :=

all: stream

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

stream: $(BIN_PATH)/stream

$(BIN_PATH)/stream: $(BUILD_PATH)/stream.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
