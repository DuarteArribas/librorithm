#include<stdio.h>
#include<stdlib.h>
#include"mem.h"

/**
 * Handles malloc allocation.
 * If the memory cannot be allocated, it handles it properly by exiting the program.
 * @param size the initial size of the array (should account for different size objects)
 * @return the pointer to the new allocated memory
 */
void *memalloc(size_t size){
  void *temp=malloc(size);
  if(temp==NULL){
    fprintf(stderr,"ERROR: Could not allocate memory! Stopping program execution.\n");
    exit(MEMORY_ERROR);
  }
  return temp;
}

/**
 * Handles realloc allocation.
 * If the memory cannot be reallocated, it handles it properly by exiting the program.
 * @param *ptr the pointer to the previous allocated memory
 * @param newSize the new size of the array (should account for different size objects)
 * @return the pointer to the new allocated memory
 */
void *memrealloc(void *ptr,size_t newSize){
  void *temp=realloc(ptr,newSize);
  if(temp==NULL){
    fprintf(stderr,"ERROR: Could not reallocate memory! Stopping program execution.\n");
    clnmem(ptr);
    exit(MEMORY_ERROR);
  }
  return temp;
}

/**
 * Handles realloc allocation.
 * If the memory cannot be reallocated, it handles it properly by exiting the program.
 * @param *ptr the pointer to the previous allocated memory
 * @param *size size of the previous array to increase by 1
 * @param typeSize the size of the type
 * @return the pointer to the new allocated memory
 */
void *memreallocp(void *ptr,size_t *size,size_t typeSize){
  ++(*size);
  void *temp=realloc(ptr,*size*typeSize);
  if(temp==NULL){
    fprintf(stderr,"ERROR: Could not reallocate memory! Stopping program execution.\n");
    clnmem(ptr);
    exit(MEMORY_ERROR);
  }
  return temp;
}

/**
 * Handles realloc allocation.
 * If the memory cannot be reallocated, it handles it properly by exiting the program.
 * @param *ptr the pointer to the previous allocated memory
 * @param *size size of the previous array to decrease by 1
 * @param typeSize the size of the type
 * @return the pointer to the new allocated memory
 */
void *memreallocm(void *ptr,size_t *size,size_t typeSize){
  --(*size);
  void *temp=realloc(ptr,*size*typeSize);
  if(temp==NULL){
    fprintf(stderr,"ERROR: Could not reallocate memory! Stopping program execution.\n");
    clnmem(ptr);
    exit(MEMORY_ERROR);
  }
  return temp;
}

/**
 * Frees and clears memory spaces
 * @param *ptr the pointer the allocated memory
 */
void clnmem(void *ptr){
  free(ptr);
  ptr=NULL;
}