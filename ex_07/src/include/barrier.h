#ifndef BARRIER_H
#define BARRIER_H

#include <stdatomic.h>
#include <stdint.h>

void sync_barrier(uint32_t thread_count);

#endif
