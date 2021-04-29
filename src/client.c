//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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