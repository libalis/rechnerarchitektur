#include "vec_sum.h"

float vec_sum(float *array, uint32_t length) {
	//TODO implement
	float ret = 0.0f;
	for (uint32_t i = 0; i < length; i++) ret += array[i];
	return ret;
}
