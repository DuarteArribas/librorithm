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
ORDER_NODE_QUEUE *createqueue           (const ORDER value);
void             enqueue                (ORDER_NODE_QUEUE **front,const ORDER value);
bool             isemptyqueue           (const ORDER_NODE_QUEUE *front);
ORDER            dequeue                (ORDER_NODE_QUEUE **front);
void             freequeue              (ORDER_NODE_QUEUE **front);
ORDER            peekqueue              (ORDER_NODE_QUEUE **front);
size_t           getOrdersLeftToFulfill (ORDER_NODE_QUEUE **ordersQueue);
void             removeOrdersWithNIF    (ORDER_NODE_QUEUE **orders,uint32_t NIF);
void             replaceOrdersNIF       (ORDER_NODE_QUEUE **orders,uint32_t oldNIF,uint32_t newNIF);
uint64_t         getMemoryWasteOrders   (ORDER_NODE_QUEUE **orders);
#endif //order_h