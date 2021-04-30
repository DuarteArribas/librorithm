//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
//project includes
#include"mem.h"
#include"clientOperations.h"
#include"client.h"

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
  return head==NULL?true:false;
}

// /**
//  * Prints the client's linked list by the specified type
//  * @param *head the address of the head
//  * @param type 1 to print horizontally as an array, 2 to print vertically
//  */
// void cprintlinked(cNODE *head,size_t type){
//   if(head==NULL){
//     fprintf(stderr,"ERROR: The list is empty!\n");
//     exit(NULL_LIST);
//   }
//   switch(type){
//     case 1:
//       printf("[");
//       while(head!=NULL){
//         printf("%c,",head->data);
//         head=head->next;
//       }
//       printf("\b]\n");
//       break;
//     case 2:
//       while(head!=NULL){
//         printf("%c\n",head->data);
//         head=head->next;
//       }
//       break;
//     case 3:
//       while(head!=NULL){
//         printf("%c",head->data);
//         head=head->next;
//       }
//       printf("\n");
//       break;
//     default:
//       printf("ERROR: Wrong print type.\n");
//       break;
//   }
// }

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
 * @param value the value to search for
 * @return the client with the specified NIF or NULL if there isn't a client with that NIF
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
 * Remove the element at start position
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
    fprintf(stderr,"ERROR: There was an error removing the specified client! %zu\n",linkedlength(*head));
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

static
void printClientNumber(size_t *userCount){
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