#include <stdio.h>
#include <stdlib.h>
#include "vec_sum.h"
#include "get_time.h"

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./vecSum <array size in kiB> <minimal runtime in milliseconds>\n");
	return;
}

int main(int argc, char *argv[]) {
	uint64_t minimal_runtime = 0u;
	uint64_t actual_runtime  = 0u;
	uint64_t runs            = 0u;
	uint64_t start           = 0u;
	uint64_t stop            = 0u;

	if(argc != 3 || argv == NULL) {
		usage_msg();
		return -1;
	}

	//TODO: parse parameter: size of the vector in KiB
	char *size = argv[0];
	char *time = argv[1];
	long size_parsed = strtol(size, NULL, 0);
	long time_parsed = strtol(time, NULL, 0);

	//TODO: allocate memory and initialize it
	float *array = malloc(size_parsed*1024);
	for (int i = 0; i < size_parsed*256; i++) array[i] = 0.1f + i;

	//TODO: measurement with a runtime of at least 1 s
	minimal_runtime = time_parsed;

	for(runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
		start = get_time_us();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			vec_sum(array, size_parsed*256u);
		}
		stop  = get_time_us();
		actual_runtime = stop - start;
	}
 
	//TODO: calculate and print updates per second

	//fprintf(stdout, "%llu,%lf,%llu,%llu\n", (uint64_t) 0, 0.0, (uint64_t) 0, (uint64_t) 0);
	fprintf(stdout, "%lu,%lf,%lu,%lu\n", (uint64_t) size_parsed, size_parsed*256.0 / actual_runtime, (uint64_t) actual_runtime, (uint64_t) minimal_runtime);

	return 0;
}
