#include"inttypes.h"
#ifndef CLIENTOPERATIONS_H
#define CLIENTOPERATIONS_H
//structs
typedef struct CLIENT{
  uint32_t NIF;
  char name[255],address[255],phoneNumber[17];
}CLIENT;
//function prototypes
CLIENT newClient(void);
#endif //clientOperations_h