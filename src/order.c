//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
//project includes
#include"mem.h"
#include"orderOperations.h"
#include"order.h"
//global variables
ORDER_NODE_QUEUE *orderQueue;

/**
 * Creates an order queue with the specified order
 * @param value the value to be the front of the queue
 * @return the address of the front
 */
ORDER_NODE_QUEUE *createqueue(ORDER value){
  ORDER_NODE_QUEUE *front=memalloc(sizeof(ORDER_NODE_QUEUE));
  front->data=value;
  front->previous=NULL;
  return front;
}

/**
 * Enqueues the specfied element to the back of the orders' queue
 * @param **front the address of the address of the front of the queue
 * @param value the new value to enqueue into the queue
 */
void enqueue(ORDER_NODE_QUEUE **front,ORDER value){
  if(*front==NULL){
    fprintf(stderr,"ERROR: The queue is empty, thus can't be enqueued\n");
    return;
  }
  ORDER_NODE_QUEUE *temp=*front;
  while(temp->previous!=NULL){
    temp=temp->previous;
  }
  ORDER_NODE_QUEUE *newBack=createqueue(value);
  temp->previous=newBack;
}

/**
 * Checks if the queue is empty
 * @param *front the address of the front
 * @return true if the queue is empty and false otherwise
 */
bool isemptyqueue(ORDER_NODE_QUEUE *front){
  return front==NULL;
}

/**
 * Dequeues the front element from the orders' queue
 * @param **front the address of the address of the front
 * @return the dequeued element
 */
ORDER dequeue(ORDER_NODE_QUEUE **front){
  if(*front==NULL){
    fprintf(stderr,"ERROR: The queue is empty, thus can't be dequeued\n");
    exit(EMPTY_QUEUE);
  }
  ORDER_NODE_QUEUE *temp=*front;
  *front=temp->previous;
  ORDER tempNum=temp->data;
  clnmem(temp);
  return tempNum;
}

/**
 * Dequeues and frees the whole orders' queue
 * @param **front the address of the address of the front
 */
void freequeue(ORDER_NODE_QUEUE **front){
  while(*front!=NULL){
    dequeue(front);
  }
}

/**
 * Gets the front element of the orders' queue
 * @param **front the address of the address of the front
 * @return the front element
 */
ORDER peekqueue(ORDER_NODE_QUEUE **front){
  if(*front==NULL){
    fprintf(stderr,"ERROR: The queue is empty, and thus cannot be peeked!\n");
    exit(EMPTY_QUEUE);
  }
  return (*front)->data;
}