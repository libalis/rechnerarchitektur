#include "vec_sum.h"

#ifndef NUMBER
	#define NUMBER (0)
#endif

float vec_sum(float *array, uint32_t length) {
	//TODO implement
	#if NUMBER == 0
		float ret = 0.0f;
		#pragma novector
		#pragma nounroll
		for (int i = 0; i < length; i++) ret += array[i];
		return ret;
	#elif NUMBER == 2
		float sum[2] = { 0.0f, 0.0f };
		uint32_t remainder = length % 2;
		#pragma novector
		#pragma nounroll
		for (int i = 0; i < length-remainder; i+=2) {
			sum[0] += array[i];
			sum[1] += array[i+1];
		}
		sum[0] += sum[1];
		if(remainder) sum[0] += array[length-1];
		return sum[0];
	#elif NUMBER == 3
		float sum[3] = { 0.0f, 0.0f, 0.0f };
		uint32_t remainder = length % 3;
		#pragma novector
		#pragma nounroll
		for (int i = 0; i < length-remainder; i+=3) {
			sum[0] += array[i];
			sum[1] += array[i+1];
			sum[2] += array[i+2];
		}
		sum[0] += sum[1];
		sum[0] += sum[2];
		if(remainder == 1) sum[0] += array[length-1];
		else if(remainder == 2)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
		}
		return sum[0];
	#elif NUMBER == 4
		float sum[3] = { 0.0f, 0.0f, 0.0f, 0.0f};
		uint32_t remainder = length % 4;
		#pragma novector
		#pragma nounroll
		for (int i = 0; i < length-remainder; i+=4) {
			sum[0] += array[i];
			sum[1] += array[i+1];
			sum[2] += array[i+2];
			sum[3] += array[i+3];
		}
		sum[0] += sum[1];
		sum[0] += sum[2];
		sum[0] += sum[3];
		if(remainder == 1) sum[0] += array[length-1];
		else if(remainder == 2)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
		}
		else if(remainder == 3)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
			sum[0] += array[length-3];
		}
		return sum[0];
	#elif NUMBER == 8
		float sum[8] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
		uint32_t remainder = length % 8;
		#pragma novector
		#pragma nounroll
		for (int i = 0; i < length-remainder; i+=4) {
			sum[0] += array[i];
			sum[1] += array[i+1];
			sum[2] += array[i+2];
			sum[3] += array[i+3];
			sum[4] += array[i+4];
			sum[5] += array[i+5];
			sum[6] += array[i+6];
			sum[7] += array[i+7];
		}
		sum[0] += sum[1];
		sum[0] += sum[2];
		sum[0] += sum[3];
		sum[0] += sum[4];
		sum[0] += sum[5];
		sum[0] += sum[6];
		sum[0] += sum[7];
		if(remainder == 1) sum[0] += array[length-1];
		else if(remainder == 2)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
		}
		else if(remainder == 3)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
			sum[0] += array[length-3];
		}
		else if(remainder == 4)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
			sum[0] += array[length-3];
			sum[0] += array[length-4];
		}
		else if(remainder == 5)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
			sum[0] += array[length-3];
			sum[0] += array[length-4];
			sum[0] += array[length-5];
		}
		else if(remainder == 6)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
			sum[0] += array[length-3];
			sum[0] += array[length-4];
			sum[0] += array[length-5];
			sum[0] += array[length-6];
		}
		else if(remainder == 7)  {
			sum[0] += array[length-1];
			sum[0] += array[length-2];
			sum[0] += array[length-3];
			sum[0] += array[length-4];
			sum[0] += array[length-5];
			sum[0] += array[length-6];
			sum[0] += array[length-7];
		return sum[0];
 	#endif
}
