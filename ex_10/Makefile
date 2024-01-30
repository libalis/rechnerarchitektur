.PHONY: all clean dgemm_cpu dgemm_gpu

ROOT_PATH  := .
SRC_PATH   := $(ROOT_PATH)/src
BUILD_PATH := $(ROOT_PATH)/build
BIN_PATH   := $(ROOT_PATH)/bin

INC_PATH  := $(SRC_PATH)/include
INC_DIRS  := $(sort $(shell find $(INC_PATH) -type d))
INC_FLAGS := $(addprefix -iquote ,$(INC_DIRS))

CC      := icc
CFLAGS  := -Wall -pedantic -Werror -qopt-streaming-stores always -O3 -fopenmp -mkl

LDFLAGS :=

NVCC			:= nvcc
NVCC_CFLAGS		:= -ccbin $(CC) -arch sm_86 -lcublas -lcurand
NVCC_INC_FLAGS	:= $(addprefix -I ,$(INC_DIRS))

all: dgemm_cpu dgemm_gpu

clean:
	rm -rf $(BUILD_PATH) $(BIN_PATH)

dgemm_cpu: $(BIN_PATH)/dgemm_cpu

$(BIN_PATH)/dgemm_cpu: $(BUILD_PATH)/dgemm_cpu.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

dgemm_gpu: $(BIN_PATH)/dgemm_gpu

$(BIN_PATH)/dgemm_gpu: $(BUILD_PATH)/dgemm_gpu.o $(BUILD_PATH)/get_time.o
	mkdir -p $(dir $@)
	$(NVCC) $(NVCC_CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_PATH)/dgemm_gpu.o: $(SRC_PATH)/dgemm_gpu.cu
	mkdir -p $(dir $@)
	$(NVCC) $(NVCC_INC_FLAGS) $(NVCC_CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -MMD -MP -c $< -o $@
