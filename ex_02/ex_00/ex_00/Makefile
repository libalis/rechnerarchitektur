.PHONY: all clean vecSum

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

all: vecSum vecSum_2 vecSum_3 vecSum_4 vecSum_8

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

vecSum: $(BIN_PATH)/vecSum
vecSum_2: $(BIN_PATH)/vecSum_2
vecSum_3: $(BIN_PATH)/vecSum_3
vecSum_4: $(BIN_PATH)/vecSum_4
vecSum_8: $(BIN_PATH)/vecSum_8

$(BIN_PATH)/vecSum: $(BUILD_PATH)/main.o $(BUILD_PATH)/vec_sum.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_PATH)/vecSum_2: $(BUILD_PATH)/main.o $(BUILD_PATH)/vec_sum.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=2 $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_PATH)/vecSum_3: $(BUILD_PATH)/main.o $(BUILD_PATH)/vec_sum.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=3 $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_PATH)/vecSum_4: $(BUILD_PATH)/main.o $(BUILD_PATH)/vec_sum.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=4 $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_PATH)/vecSum_8: $(BUILD_PATH)/main.o $(BUILD_PATH)/vec_sum.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=8 $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
