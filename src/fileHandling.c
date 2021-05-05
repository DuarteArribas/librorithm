//global includes
#include<stdio.h>
#include<stdlib.h>
//project includes
#include"fileHandling.h"
#include"mem.h"
#include"client.h"
#include"order.h"
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;


/**
 * Creates and overrides new files
 */
void newFile(void){
  FILE *clients=fopen("in/binStructures/clients.bin","wb");
  FILE *books=fopen("in/binStructures/books.bin","wb");
  FILE *orders=fopen("in/binStructures/orders.bin","wb");
  if(clients==NULL||books==NULL||orders==NULL){
    perror("ERROR opening the file! Aborting...");
    exit(FILE_ERROR);
  }
  fclose(clients);
  fclose(books);
  fclose(orders);
}

/**
 * Creates and overrides new dataStructures
 */
void newDataStructures(void){
  freelinked(clientlist);
  clientlist=NULL;
}

static void writeClients(FILE *clients){
  clientNODE *clientlistTemp=clientlist;
  while(clientlistTemp!=NULL){
    fwrite(&(clientlistTemp->data),sizeof(CLIENT),1,clients);
    if(clientlistTemp->data.orders!=NULL){
      fwrite(clientlistTemp->data.orders,sizeof(ORDER),clientlistTemp->data.numOfOrders,clients);
    }
    clientlistTemp=clientlistTemp->next;
  }
}

static void writeOrders(FILE *orders){
  ORDER_NODE_QUEUE *orderQueueTemp=NULL;
  while(orderQueue!=NULL){
    ORDER orderTemp=dequeue(&orderQueue);
    fwrite(&orderTemp,sizeof(ORDER),1,orders);
    if(isemptyqueue(orderQueueTemp)){
      orderQueueTemp=createqueue(orderTemp);
    }
    else{
      enqueue(&orderQueueTemp,orderTemp);
    }
  }
  orderQueue=orderQueueTemp;
}

static void readClients(FILE *clients){
  CLIENT clientTemp;
  while(fread(&clientTemp,sizeof(CLIENT),1,clients)){
    if(clientTemp.numOfOrders!=0){
      clientTemp.orders=memalloc(clientTemp.numOfOrders*sizeof(ORDER));
      for(size_t i=0;i<clientTemp.numOfOrders;i++){
        fread(&(clientTemp.orders[i]),sizeof(ORDER),1,clients);
      }
    }
    if(isemptylist(clientlist)){
      clientlist=createLinked(clientTemp);
    }
    else{
      eappendlinked(clientlist,clientTemp);
    }
  }
}

static void readOrders(FILE *orders){
  ORDER orderTemp;
  while(fread(&orderTemp,sizeof(ORDER),1,orders)){
    if(isemptyqueue(orderQueue)){
      orderQueue=createqueue(orderTemp);
    }
    else{
      enqueue(&orderQueue,orderTemp);
    }
  }
}

/**
 * Saves the contents of the three structures of the program into their respective files
 */
void saveFile(void){
  FILE *clients=fopen("in/binStructures/clients.bin","wb+");
  FILE *books=fopen("in/binStructures/books.bin","wb+");
  FILE *orders=fopen("in/binStructures/orders.bin","wb+");
  if(clients==NULL||books==NULL||orders==NULL){
    perror("ERROR opening the file! Aborting...");
    exit(FILE_ERROR);
  }
  writeClients(clients);
  writeOrders(orders);
  fclose(clients);
  fclose(books);
  fclose(orders);
}

/**
 * Opens the contents of the three structures on the files to their respective structures
 */
void openFile(void){
  newDataStructures();
  FILE *clients=fopen("in/binStructures/clients.bin","rb");
  FILE *books=fopen("in/binStructures/books.bin","rb");
  FILE *orders=fopen("in/binStructures/orders.bin","rb");
  if(clients==NULL||books==NULL||orders==NULL){
    perror("ERROR opening the file! Aborting...");
    exit(FILE_ERROR);
  }
  readClients(clients);
  readOrders(orders);
  fclose(clients);
  fclose(books);
  fclose(orders);
}