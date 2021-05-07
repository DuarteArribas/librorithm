#include<inttypes.h>
#include<stdbool.h>
#ifndef ORDEROPERATIONS_H
#define ORDEROPERATIONS_H
//structs
typedef struct ORDER{
  long int ISBN;
  uint32_t NIF;
  char date[11];
  uint16_t quantity;
  double totalPrice;
}ORDER;
//function prototypes
ORDER    newOrder           (void);
void     updateClientOrders (const uint32_t NIF,const ORDER order);
void     getDate            (char *date);
void     getYear            (char *yearTemp,uint16_t *year);
void     getMonth           (char *monthTemp,uint8_t *month);
void     getDay             (char *dayTemp,uint8_t *day,const uint8_t MAX_DAY);
bool     getQuantity        (uint16_t *quantity,long int ISBN);
bool     isSameOrder        (const ORDER order1,const ORDER order2);
void     printOrder         (const ORDER order,const size_t orderNum);
#endif //orderOperations_h