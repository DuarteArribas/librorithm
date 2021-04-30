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
clientNODE *createLinked        (CLIENT value);
void       freelinked           (clientNODE *head);
bool       isemptylist          (clientNODE *head);
size_t     linkedlength         (clientNODE *head);
bool       lsearchlinked        (clientNODE *head,uint32_t value);
clientNODE *getSearchlinked     (clientNODE *head,uint32_t value);
void       changeClient         (clientNODE *head,CLIENT client);
void       sremovelinked        (clientNODE **head);
void       removelinked         (clientNODE **head,size_t index);
void       removeClient         (clientNODE **head,uint32_t NIF);
void       consultClientNIF     (clientNODE *head,uint32_t NIF);
void       consultClientName    (clientNODE *head,char *name);
void       consultClientAddress (clientNODE *head,char *address);
void       consultAll           (clientNODE *head);
void       sappendlinked        (clientNODE **head,CLIENT value);
void       eappendlinked        (clientNODE *head,CLIENT value);
#endif //client_h