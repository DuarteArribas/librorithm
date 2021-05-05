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
CLIENT   newClient          (void);
uint32_t getNIF             (void);
void     getName            (char *name);
void     getAddress         (char *address);
void     getPhoneNumber     (char *phoneNumber);
void     printClient        (CLIENT client);
void     printClientReverse (CLIENT client);
void     getDayMonthYear    (char *date,uint8_t *day,uint8_t *month,uint16_t *year);
int8_t   compareDates       (char *date1,char *date2);
#endif //clientOperations_h