#include<inttypes.h>
#include"orderOperations.h"
#ifndef CLIENTOPERATIONS_H
#define CLIENTOPERATIONS_H
//structs
typedef struct CLIENT{
  uint32_t NIF;
  char name[255],address[255],phoneNumber[18];
  size_t numOfOrders;
  ORDER *orders;
}CLIENT;
//function prototypes
CLIENT   newClient      (void);
uint32_t getNIF         (void);
void     getName        (char *name);
void     getAddress     (char *address);
void     getPhoneNumber (char *phoneNumber);
void     printClient    (CLIENT client);
#endif //clientOperations_h