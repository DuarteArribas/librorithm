#include<inttypes.h>
#include"orderOperations.h"
#ifndef CLIENTOPERATIONS_H
#define CLIENTOPERATIONS_H
//definitions
#define HEADER 1
#define FOOTER 2
//structs
typedef struct CLIENT{
  uint32_t NIF;
  char name[255],address[255],phoneNumber[18];
  size_t numOfOrders;
  ORDER *orders;
}CLIENT;
//function prototypes
CLIENT   newClient            (void);
bool     getNIF               (uint32_t *NIF);
bool     getNIFChange         (uint32_t *NIF,uint32_t oldNIF);
bool     getName              (char *name);
bool     getAddress           (char *address);
bool     getPhoneNumber       (char *phoneNumber);
bool     getPhoneNumberChange (char *phoneNumber);
void     printClient          (const CLIENT client);
void     printClientReverse   (const CLIENT client);
void     getDayMonthYear      (char *date,uint8_t *day,uint8_t *month,uint16_t *year);
int8_t   compareDates         (char *date1,char *date2);
#endif //clientOperations_h