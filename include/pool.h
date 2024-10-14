#ifndef POOL_H
#define POOL_H
#include <stddef.h>

typedef struct {
	void* memory;
	size_t chunkSize;
	size_t capacity;
	void** freeList;
	size_t freeCount;
}PoolAllocator;

//Initialize Pool allocator 
// chunkSize = size of each component
// capacity = number of Components
int pool_init(PoolAllocator* pool, size_t chunkSize, size_t capacity);

void* pool_allocate(PoolAllocator* pool);

void pool_free(PoolAllocator* pool, void* chunk);

void pool_destroy(PoolAllocator* pool);

#endif
