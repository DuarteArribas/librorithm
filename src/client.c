//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
//project includes
#include"mem.h"
#include"orderOperations.h"
#include"clientOperations.h"
#include"client.h"
//global variables
clientNODE *clientlist;

/**
 * Creates a client linked list with the specified element
 * @param value the value to add to the head of the list
 * @return the address of the head
 */
clientNODE *createLinked(CLIENT value){
  clientNODE *head=memalloc(sizeof(clientNODE));
  head->data=value;
  head->next=NULL;
  return head;
}

/**
 * Cleans the whole client's linked list, freeing the memory
 * @param *head the address of the head
 */
void freelinked(clientNODE *head){
  clientNODE *temp=head;
  while(head!=NULL){
    temp=head->next;
    clnmem(head->data.orders);
    clnmem(head);
    head=temp;
  }
}

/**
 * Checks if the list is empty
 * @param *head the address of the head
 * @return true if the list is empty and false otherwise
 */
bool isemptylist(clientNODE *head){
  return head==NULL;
}

/**
 * Gets the length of the client's linked list
 * @param *head the address of the head
 */
size_t linkedlength(clientNODE *head){
  if(head==NULL){
    return 0;
  }
  size_t count=0;
  while(head!=NULL){
    ++count;
    head=head->next;
  }
  return count;
}

/**
 * Searches for the specified NIF in the clients' linked list
 * @param *head the address of the head
 * @param value the NIF to search for
 * @return true if the NIF is in the list or false otherwise
 */
bool lsearchlinked(clientNODE *head,uint32_t value){
  if(head==NULL){
    return false;
  }
  while(head!=NULL){
    if(head->data.NIF==value){
      return true;
    }
    head=head->next;
  }
  return false;
}

/**
 * Searches for the specified NIF in the clients' linked list
 * @param *head the address of the head
 * @param value the value to search for
 * @return the client with the specified NIF or NULL if there isn't a client with that NIF
 */
clientNODE *getSearchlinked(clientNODE *head,uint32_t value){
  if(head==NULL){
    return NULL;
  }
  while(head!=NULL){
    if(head->data.NIF==value){
      return head;
    }
    head=head->next;
  }
  return NULL;
}

/**
 * Searches for the specified ORDER in the clients' linked list's orders' array
 * @param *head the address of the head
 * @param value the value to search for
 * @param *pos the index of that ORDER in the client's orders' array
 * @return the client with the specified ORDER or NULL if there isn't a client with that ORDER
 */
clientNODE *getSearchlinkedByOrder(clientNODE *head,ORDER value,size_t *pos){
  if(head==NULL){
    return NULL;
  }
  while(head!=NULL){
    for(size_t i=0;i<head->data.numOfOrders;i++){
      if(isSameOrder((head->data.orders)[i],value)){
        *pos=i;
        return head;
      }
    }
    head=head->next;
  }
  return NULL;
}

/**
 * Changes the specified client's properties for the new ones in the clients' linked list
 * @param *head the address of the head
 * @param client the client to change
 */
void changeClient(clientNODE *head,CLIENT client){
  if(head==NULL){
    return;
  }
  uint32_t newNIF;
  char newName[255],newAddress[255],newPhoneNumber[18];
  newNIF=getNIF();
  getName(newName);
  getAddress(newAddress);
  getPhoneNumber(newPhoneNumber);
  while(head!=NULL){
    if(head->data.NIF==client.NIF){
      head->data.NIF=newNIF;
      strcpy(head->data.name,newName);
      strcpy(head->data.address,newAddress);
      strcpy(head->data.phoneNumber,newPhoneNumber);
      return;
    }
    head=head->next;
  }
}

/**
 * Remove the client at the start position
 * @param **head the address of the address of the head
 */
void sremovelinked(clientNODE **head){
  clientNODE *temp=*head;
  *head=temp->next;
  clnmem(temp);
}

/**
 * Remove the element at the specified index
 * @param **head the address of the address of the head
 * @param index of the node to remove
 */
void removelinked(clientNODE **head,size_t index){
  if(index+1>linkedlength(*head)){
    fprintf(stderr,"ERROR: There was an error removing the specified client!\n");
    return;
  }
  if(index==0){
    sremovelinked(head);
    return;
  }
  clientNODE *temp=*head,*temp2;
  for(;index>0;index--){
    temp2=temp;
    temp=temp->next;
  }
  temp2->next=temp->next;
  clnmem(temp);
}

/**
 * Removes the client with the specified NIF
 * @param **head the address of the address of the head
 * @param NIF the NIF of the client to remove
 */
void removeClient(clientNODE **head,uint32_t NIF){
  if(*head==NULL){
    return;
  }
  size_t clientIndex=0;
  while(*head!=NULL){
    if((*head)->data.NIF==NIF){
      removelinked(head,clientIndex);
      return;
    }
    ++clientIndex;
    *head=(*head)->next;
  }
}

/**
 * Consults the client with the specified NIF
 * @param *head the address of the head
 * @param NIF the NIF of the client to remove
 */
void consultClientNIF(clientNODE *head,uint32_t NIF){
  if(head==NULL){
    fprintf(stderr,"ERROR: There are no clients on the system!\n");
    return;
  }
  while(head!=NULL){
    if(head->data.NIF==NIF){
      printClient(head->data);
      char dummy[1000];
      fgets(dummy,1000,stdin);
      return;
    }
    head=head->next;
  }
  fprintf(stderr,"ERROR: There isn't a client with the specified NIF! Please try again.\n");
  return;
}

static void printClientNumber(size_t *userCount){
  size_t maxEqual=13+floor(log10(*userCount))+1;
  size_t maxSpace=2+floor(log10(*userCount))+1;
  for(size_t i=0;i<maxEqual;i++){
    printf("=");
  }
  printf("\n");
  for(size_t i=0;i<maxSpace;i++){
    printf(" ");
  }
  printf("Client %zu",(*userCount)++);
  maxSpace--;
  for(size_t i=0;i<maxSpace;i++){
    printf(" ");
  }
  printf("\n");
  for(size_t i=0;i<maxEqual;i++){
    printf("=");
  }
  printf("\n");
}

/**
 * Consults the client with the specified name
 * @param *head the address of the head
 * @param *name the name of the client to remove
 */
void consultClientName(clientNODE *head,char *name){
  if(head==NULL){
    fprintf(stderr,"ERROR: There are no clients on the system!\n");
    return;
  }
  bool existUsers=false;
  size_t userCount=1;
  while(head!=NULL){
    if(strcmp(head->data.name,name)==0){
      printClientNumber(&userCount);
      existUsers=true;
      printClient(head->data);
      char dummy[1000];
      fgets(dummy,1000,stdin);
    }
    head=head->next;
  }
  if(existUsers){return;}
  fprintf(stderr,"ERROR: There isn't a client with the specified name! Please try again.\n");
  return;
}

/**
 * Consults the client with the specified address
 * @param *head the address of the head
 * @param *address the address of the client to remove
 */
void consultClientAddress(clientNODE *head,char *address){
  if(head==NULL){
    fprintf(stderr,"ERROR: There are no clients on the system!\n");
    return;
  }
  bool existUsers=false;
  size_t userCount=1;
  while(head!=NULL){
    if(strcmp(head->data.address,address)==0){
      printClientNumber(&userCount);
      existUsers=true;
      printClient(head->data);
      char dummy[1000];
      fgets(dummy,1000,stdin);
    }
    head=head->next;
  }
  if(existUsers){return;}
  fprintf(stderr,"ERROR: There isn't a client with the specified address! Please try again.\n");
  return;
}

/**
 * Consults every client
 * @param *head the address of the head
 */
void consultAll(clientNODE *head){
  if(head==NULL){
    fprintf(stderr,"ERROR: There are no clients on the system!\n");
    return;
  }
  size_t userCount=1;
  while(head!=NULL){
    printClientNumber(&userCount);
    printClient(head->data);
    char dummy[1000];
    fgets(dummy,1000,stdin);
    head=head->next;
  }
  return;
}

/**
 * Append element at the start of the client's linked list
 * @param **head the address of the address of the head
 * @param value the value to append
 */
void sappendlinked(clientNODE **head,CLIENT value){
  if(*head==NULL){
    fprintf(stderr,"ERROR: The list is empty!\n");
    exit(NULL_LIST);
  }
  clientNODE *newElement=memalloc(sizeof(clientNODE));
  newElement->data=value;
  newElement->next=*head;
  *head=newElement;
}

/**
 * Append element at the end of the client's linked list
 * @param *head the address of the head
 * @param value the value to append
 */
void eappendlinked(clientNODE *head,CLIENT value){
  if(head==NULL){
    fprintf(stderr,"ERROR: The list is empty!\n");
    exit(NULL_LIST);
  }
  while(head!=NULL){
    if(head->next==NULL){
      break;
    }
    head=head->next;
  }
  clientNODE *newElement=memalloc(sizeof(clientNODE));
  newElement->data=value;
  newElement->next=NULL;
  head->next=newElement;
}

/**
 * Computes the memory waste from the clients' list
 * @param *head the address of the head
 */
uint64_t getMemoryWasteClients(clientNODE *head){
  uint64_t memoryWaste=0;
  while(head!=NULL){
    memoryWaste+=(255-strlen(head->data.name)+255-strlen(head->data.address)+18-strlen(head->data.phoneNumber));
    for(size_t i=0;i<head->data.numOfOrders;i++){
      memoryWaste+=(11-strlen(head->data.orders[i].date));
    }
    head=head->next;
  }
  return memoryWaste;
}

static void copylinkedlist(clientNODE **dest,clientNODE *src){
  *dest=createLinked(src->data);
  src=src->next;
  while(src!=NULL){
    eappendlinked(*dest,src->data);
    src=src->next;
  }
}

static clientNODE* mergeHelper(clientNODE* list1,clientNODE* list2){
  clientNODE *temp=NULL;
  //base cases
  if(list1==NULL){
    return list2;
  }
  else if(list2==NULL){
    return list1;
  }
  //recursive cases
  //check if number of orders (purchases) is lower than the other
  if(list1->data.numOfOrders<=list2->data.numOfOrders){
    temp=list1;
    temp->next=mergeHelper(list1->next,list2);
  }
  else{
    temp=list2;
    temp->next=mergeHelper(list1,list2->next);
  }
  return temp;
}

static void splitMerge(clientNODE *src,clientNODE **front,clientNODE **back){
  clientNODE *l1=src->next;
  clientNODE *l2=src;
  while(l1!=NULL){
    l1=l1->next;
    if(l1!=NULL){
      l2=l2->next;
      l1=l1->next;
    }
  }
  *front=src;
  *back=l2->next;
  l2->next=NULL;
}

static void MergeSort(struct clientNODE **list){
  clientNODE *head=*list;
  clientNODE *left;
  clientNODE *right;
  //base case
  if((head==NULL)||(head->next==NULL)){
    return;
  }
  //recursive
  splitMerge(head, &left, &right);
  MergeSort(&left);
  MergeSort(&right);
  *list=mergeHelper(left,right);
}

static void printReverse(clientNODE *head){
  if(head==NULL){
    return;
  }
  printReverse(head->next);
  printClientReverse(head->data);
}

/**
 * Shows the clients in reverse order of number of purchases
 */
void showClientsDec(void){
  clientNODE *clientTemp=NULL;
  copylinkedlist(&clientTemp,clientlist);
  MergeSort(&clientTemp);
  printReverse(clientTemp);
  clnmem(clientTemp);
}

/**
 * Gets the client with most books
 * @return the client with most books
 */
CLIENT clientWithMostBooks(void){
  size_t max=0,maxTemp=0;
  CLIENT maxClient;
  clientNODE *clientTemp=clientlist;
  while(clientTemp!=NULL){
    for(size_t i=0;i<clientTemp->data.numOfOrders;i++){
      maxTemp+=clientTemp->data.orders[i].quantity;
    }
    if(maxTemp>max){
      max=maxTemp;
      maxClient=clientTemp->data;
    }
    maxTemp=0;
    clientTemp=clientTemp->next;
  }
  return maxClient;
}

/**
 * Gets the number of books at the specified date month/year
 * @param *monthTemp the month
 * @param *year the year
 * @return the number of books at the specified date
 */
size_t getNumOfBooks(char *monthTemp,char *yearTemp){
  size_t numOfBooks=0;
  clientNODE *clientTemp=clientlist;
  while(clientTemp!=NULL){
    for(size_t i=0;i<clientTemp->data.numOfOrders;i++){
      if(clientTemp->data.orders[i].date[3]==monthTemp[0]&&clientTemp->data.orders[i].date[4]==monthTemp[1]){
        bool canCount=true;
        for(size_t j=0;j<strlen(clientTemp->data.orders[i].date)-6;j++){
          if(clientTemp->data.orders[i].date[j+6]!=yearTemp[j]){
            canCount=false;
            break;
          }
        }
        if(canCount){
          numOfBooks+=clientTemp->data.orders[i].quantity;
        }
      }
    }
    clientTemp=clientTemp->next;
  }
  return numOfBooks;
}

/**
 * Prints the latest date, given an ISBN
 * @param ISBN the specified ISBN
 */
void latestDateByBook(long int ISBN){
  clientNODE *clientTemp=clientlist;
  char maxDate[11]="00-00-0000";
  const char defaultDate[11]="00-00-0000";
  while(clientTemp!=NULL){
    for(size_t i=0;i<clientTemp->data.numOfOrders;i++){
      if(clientTemp->data.orders[i].ISBN==ISBN){
        if(compareDates(clientTemp->data.orders[i].date,maxDate)==1){
          strcpy(maxDate,clientTemp->data.orders[i].date);
        }  
      }
    }
    clientTemp=clientTemp->next;
  }
  if(strcmp(defaultDate,maxDate)==0){
    fprintf(stderr,"ERROR: There aren't any books ordered with that ISBN!\n");
  }
  else{
    printf("======= DATE: %s =======\n",maxDate);
  }
}

/**
 * Prints the number of books of a given client, given the NIF
 * @param NIF the specified NIF
 */
void numBooksByClient(uint32_t NIF){
   clientNODE *clientTemp=clientlist;
   size_t numOfBooks=0;
   while(clientTemp!=NULL){
    if(clientTemp->data.NIF==NIF){
      for(size_t i=0;i<clientTemp->data.numOfOrders;i++){
        numOfBooks+=clientTemp->data.orders[i].quantity;
      }  
    }
    clientTemp=clientTemp->next;
  }
  printf("======= NUM OF BOOKS: %zu =======\n",numOfBooks);
}

/**
 * Prints the client that wasted more money in the specified date
 * @param month the specified month
 * @param year the specified year
 */
void clientThatWastedMore(uint8_t month,uint16_t year){
   clientNODE *clientTemp=clientlist;
   CLIENT client;
   double totalPrice=0,maxTotalPrice=-1;
   uint8_t currMonth,currDay;
   uint16_t currYear;
   while(clientTemp!=NULL){
    for(size_t i=0;i<clientTemp->data.numOfOrders;i++){
      getDayMonthYear(clientTemp->data.orders[i].date,&currDay,&currMonth,&currYear);
      if(currMonth==month&&currYear==year){
        totalPrice+=clientTemp->data.orders[i].totalPrice;
      }
    }
    if(totalPrice>maxTotalPrice){
      maxTotalPrice=totalPrice;
      client=clientTemp->data;
    }
    totalPrice=0;
    clientTemp=clientTemp->next;
  }
  if(fabs(maxTotalPrice-1)<0.001){
    fprintf(stderr,"ERROR: There aren't any clients that wasted money on that date!\n");
  }
  else{
    printClient(client);
  }
}