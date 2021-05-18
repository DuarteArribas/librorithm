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
clientNODE *createLinked            (const CLIENT value);
void       freelinked               (clientNODE *head);
void       freelinked2              (clientNODE *head);
bool       isemptylist              (const clientNODE *head);
size_t     linkedlength             (clientNODE *head);
bool       lsearchlinked            (clientNODE *head,const uint32_t value);
clientNODE *getSearchlinked         (clientNODE *head,const uint32_t value);
clientNODE *getSearchlinkedByOrder  (clientNODE *head,const ORDER value,size_t *pos);
void       changeClient             (clientNODE *head,const CLIENT client);
void       sremovelinked            (clientNODE **head);
void       removelinked             (clientNODE **head,size_t index);
bool       removeClient             (clientNODE **head,const uint32_t NIF);
void       consultClientNIF         (clientNODE *head,const uint32_t NIF);
void       consultClientName        (clientNODE *head,const char *name);
void       consultClientAddress     (clientNODE *head,const char *address);
void       consultAll               (clientNODE *head);
void       sappendlinked            (clientNODE **head,const CLIENT value);
void       eappendlinked            (clientNODE *head,const CLIENT value);
uint64_t   getMemoryWasteClients    (clientNODE *head);
void       showClientsDec           (void);
CLIENT     clientWithMostBooks      (void);
size_t     getNumOfBooks            (const char *monthTemp,const char *yearTemp);
void       latestDateByBook         (const long int ISBN);
void       numBooksByClient         (const uint32_t NIF);
void       clientThatWastedMore     (const uint8_t month,const uint16_t year);
void       clientsThatStartWithChar (void);
void       showBestSoldBooks        (clientNODE *clients,const size_t amount);
#endif //client_h