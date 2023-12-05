.PHONY: all clean jacobi jacobi_2 jacobi_4

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

all: jacobi jacobi_2 jacobi_4

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

jacobi: $(BIN_PATH)/jacobi
jacobi_2: $(BIN_PATH)/jacobi_2
jacobi_4: $(BIN_PATH)/jacobi_4

$(BIN_PATH)/jacobi: $(BUILD_PATH)/main.o $(BUILD_PATH)/draw.o $(BUILD_PATH)/jacobi.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_PATH)/jacobi_2: $(BUILD_PATH)/main.o $(BUILD_PATH)/draw.o $(BUILD_PATH)/jacobi_2.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/jacobi_2.o: $(SRC_PATH)/jacobi.c
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=2 $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BIN_PATH)/jacobi_4: $(BUILD_PATH)/main.o $(BUILD_PATH)/draw.o $(BUILD_PATH)/jacobi_4.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/jacobi_4.o: $(SRC_PATH)/jacobi.c
	mkdir -p $(dir $@)
	$(CC) -DNUMBER=4 $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
