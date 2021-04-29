#ifndef CLIENT_H
#define CLIENT_H
//project includes
#include"clientOperations.h"
//definitions
#define INVALID_INDEX 5
#define NULL_LIST 6
//node
typedef struct clientNODE{
  CLIENT data;
  struct clientNODE *next;
}clientNODE;
//function prototypes
#endif //client_h