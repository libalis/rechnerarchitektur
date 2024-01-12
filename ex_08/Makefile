.PHONY: all clean stream triad

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

NVCC			:= nvcc
NVCC_CFLAGS		:= -ccbin $(CC)
NVCC_INC_FLAGS	:= $(addprefix -I ,$(INC_DIRS))

COPY_TIME := -DCOPY_TIME=0

all: stream triad

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

stream: $(BIN_PATH)/stream

$(BIN_PATH)/stream: $(BUILD_PATH)/stream.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

triad: $(BIN_PATH)/triad

$(BIN_PATH)/triad: $(BUILD_PATH)/triad.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(NVCC) $(NVCC_CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/triad.o: $(SRC_PATH)/triad.cu
	mkdir -p $(dir $@)
	$(NVCC) $(COPY_TIME) $(NVCC_INC_FLAGS) $(NVCC_CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
