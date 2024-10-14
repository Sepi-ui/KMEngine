#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "logIt.h"
#include "pool.h"

int pool_init(PoolAllocator* pool, size_t chunkSize, size_t capacity) {

pool->memory = malloc(capacity* chunkSize);
if (pool->memory == NULL) {
	fatal_log("Error Allocating pool Memory");
	return -1;
	};


pool->freeList = malloc(capacity * sizeof(void*));
    if (pool->freeList == NULL) {
        fatal_log("Error Allocating pool Free List");
        free(pool->memory);  // Free the memory if allocation fails
        return -1;
    }

pool->chunkSize = chunkSize;
pool->capacity = capacity;
pool->capacity = capacity;

// Initialize the free list to point to each chunk
    for (size_t i = 0; i < capacity; ++i) {
        pool->freeList[i] = (char*)((char*)pool->memory + i * chunkSize);
    }
return 0;
}
