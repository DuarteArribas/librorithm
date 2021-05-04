#include<inttypes.h>
#ifndef ORDEROPERATIONS_H
#define ORDEROPERATIONS_H
//structs
typedef struct ORDER{
  uint32_t ISBN,NIF;
  char date[11];
  uint16_t quantity;
  double totalPrice;
}ORDER;
//function prototypes
ORDER    newOrder    (void);
void     getDate     (char *date);
uint16_t getQuantity (void);
bool     isSameOrder (ORDER order1,ORDER order2);
void     printOrder  (ORDER order,size_t orderNum);
#endif //orderOperations_h