#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<inttypes.h>
#include<math.h>
#include"orderOperations.h"
#include"clientOrder.h"
#include"mem.h"

static void shiftLeft(size_t size,ORDER *array,size_t index){
  for(size_t i=index;i<size-1;++i){
    array[i]=array[i+1];
  }
}

/**
 * Removes the value at the specified index from the orders' array, decreasing its size by 1
 * @param *size the size of the array
 * @param **array the array to remove the value
 * @param index the index of the array to remove
 */
void removeFromArray(size_t *size,ORDER **array,size_t index){
  if(index>*size){
    fprintf(stderr,"Error: could not remove from array, because index is invalid\n");
    exit(INVALID_INDEX);
  }
  shiftLeft(*size,*array,index);
  --(*size);
  *array=realloc(*array,*size*sizeof(ORDER));
}