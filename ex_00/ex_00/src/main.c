#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "vec_sum.h"
#include "get_time.h"

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./vecSum <array size in kiB> <minimal runtime in milliseconds>\n");
	return;
}

int main(int argc, char *argv[]) {
	uint64_t minimal_runtime  = 0u;
	uint64_t actual_runtime   = 0u;
	uint64_t array_size_bytes = 0u; // The allocated array size in bytes
	uint64_t runs             = 0u;
	uint64_t start            = 0u;
	uint64_t stop             = 0u;
	double   adds_per_second  = 0u;

	if(argc != 3 || argv == NULL) {
		usage_msg();
		return -1;
	}

	//TODO: parse parameter: size of the vector in KiB
	array_size_bytes = strtold(argv[1], NULL) * 1024;

	//TODO: allocate memory and initialize it
	float *array = malloc(array_size_bytes);
	for (int i = 0; i < array_size_bytes/(float)sizeof(float); i++) array[i] = i + 0.1f;

	//TODO: measurement with a runtime of at least 1 s
	minimal_runtime = strtold(argv[2], NULL);

	for(runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
		start = get_time_us();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			vec_sum(array, array_size_bytes/(float)sizeof(float));
		}
		stop  = get_time_us();
		actual_runtime = stop - start;
	}

	//TODO: calculate and print
	adds_per_second = array_size_bytes/(float)sizeof(float)/actual_runtime; // Measured performance as floating point additions per second
	fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", array_size_bytes, adds_per_second, actual_runtime, minimal_runtime);

	return 0;
}
