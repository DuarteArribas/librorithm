#ifndef MEM_H
#define MEM_H
#define MEMORY_ERROR -1
void *memalloc(size_t size);
void *memrealloc(void *ptr,size_t newSize);
void *memreallocp(void *ptr,size_t *newSize,size_t typeSize);
void *memreallocm(void *ptr,size_t *size,size_t typeSize);
void clnmem(void *ptr);
#endif