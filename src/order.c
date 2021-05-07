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
ORDER_NODE_QUEUE *createqueue(const ORDER value){
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
void enqueue(ORDER_NODE_QUEUE **front,const ORDER value){
  if(*front==NULL){
    fprintf(stderr,"\tERROR: The queue is empty, thus can't be enqueued\n");
    return;
  }
  ORDER_NODE_QUEUE *temp=*front;
  while(temp->previous!=NULL){
    temp=temp->previous;
  }
  ORDER_NODE_QUEUE *newBack=createqueue(value);
  temp->previous=newBack;
  temp=temp->previous;
}

/**
 * Checks if the queue is empty
 * @param *front the address of the front
 * @return true if the queue is empty and false otherwise
 */
bool isemptyqueue(const ORDER_NODE_QUEUE *front){
  return front==NULL;
}

/**
 * Dequeues the front element from the orders' queue
 * @param **front the address of the address of the front
 * @return the dequeued element
 */
ORDER dequeue(ORDER_NODE_QUEUE **front){
  if(*front==NULL){
    fprintf(stderr,"\tERROR: The queue is empty, thus can't be dequeued\n");
    exit(EMPTY_QUEUE);
  }
  ORDER_NODE_QUEUE *temp=*front;
  if((*front)->previous==NULL){
    ORDER tempNum=(*front)->data;
    free(*front);
    *front=NULL;
    return tempNum;
  }
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
    fprintf(stderr,"\tERROR: The queue is empty, and thus cannot be peeked!\n");
    exit(EMPTY_QUEUE);
  }
  return (*front)->data;
}

/**
 * Gets the number of orders left to fulfill
 * @param **ordersQueue the orders queue
 * @return the number of orders left to fulfill
 */
size_t getOrdersLeftToFulfill(ORDER_NODE_QUEUE **ordersQueue){
  ORDER_NODE_QUEUE *queue=NULL;
  size_t ordersCount=0;
  while(*ordersQueue!=NULL){
    ++ordersCount;
    if(isemptyqueue(queue)){
      queue=createqueue(dequeue(ordersQueue));
      continue;
    }
    enqueue(&queue,dequeue(ordersQueue));
  }
  while(queue!=NULL){
    if(isemptyqueue(*ordersQueue)){
      *ordersQueue=createqueue(dequeue(&queue));
      continue;
    }
    enqueue(ordersQueue,dequeue(&queue));
  }
  freequeue(&queue);
  return ordersCount;
}

/**
 * Removes the orders of the specified NIF
 * @param **orders the orders queue
 * @param NIF the NIF of the orders to remove
 */
void removeOrdersWithNIF(ORDER_NODE_QUEUE **orders,uint32_t NIF){
  ORDER_NODE_QUEUE *queue=NULL;
  while(*orders!=NULL){
    if((*orders)->data.NIF!=NIF){
      if(isemptyqueue(queue)){
        queue=createqueue(dequeue(orders));
        continue;
      }
      enqueue(&queue,dequeue(orders));
    }
    else{
      dequeue(orders);
    }
  }
  while(queue!=NULL){
    if(isemptyqueue(*orders)){
      *orders=createqueue(dequeue(&queue));
      continue;
    }
    enqueue(orders,dequeue(&queue));
  }
  freequeue(&queue);
}


/**
 * Replaces the NIF of the orders with oldNIF by newNIF
 * @param **orders the orders queue
 * @param oldNIF the NIF of the order
 * @param newNIF the new NIF to replace the old NIF on the order
 */
void replaceOrdersNIF(ORDER_NODE_QUEUE **orders,uint32_t oldNIF,uint32_t newNIF){
  ORDER_NODE_QUEUE *queue=NULL;
  while(*orders!=NULL){
    if((*orders)->data.NIF==oldNIF){
      (*orders)->data.NIF=newNIF;
    }
    if(isemptyqueue(queue)){
      queue=createqueue(dequeue(orders));
      continue;
    }
    enqueue(&queue,dequeue(orders));
  }
  while(queue!=NULL){
    if(isemptyqueue(*orders)){
      *orders=createqueue(dequeue(&queue));
      continue;
    }
    enqueue(orders,dequeue(&queue));
  }
  freequeue(&queue); 
}