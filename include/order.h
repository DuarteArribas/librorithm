#ifndef ORDER_H
#define ORDER_H
//project includes
#include"orderOperations.h"
//definitions
#define EMPTY_QUEUE 6
//node
typedef struct ORDER_NODE_QUEUE{
  ORDER data;
  struct ORDER_NODE_QUEUE *previous;
}ORDER_NODE_QUEUE;
//function prototypes
ORDER_NODE_QUEUE *createqueue (ORDER value);
void             enqueue      (ORDER_NODE_QUEUE **front,ORDER value);
bool             isemptyqueue (ORDER_NODE_QUEUE *front);
ORDER            dequeue      (ORDER_NODE_QUEUE **front);
void             freequeue    (ORDER_NODE_QUEUE **front);
ORDER            peekqueue    (ORDER_NODE_QUEUE **front);
#endif //order_h