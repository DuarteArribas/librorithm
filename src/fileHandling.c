//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//project includes
#include"fileHandling.h"
#include"librorithm.h"
#include"mem.h"
#include"client.h"
#include"order.h"
//global variables
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;
//static function prototypes
static bool   canDeleteFiles (void);
static bool   canDeleteDS    (void);
static void   writeClients   (FILE *clients);
static void   writeClient    (const clientNODE *client,FILE *clientsFile);
static void   writeOrders    (FILE *ordersFile);
static void   writeOrder     (ORDER_NODE_QUEUE **ordersTemp,FILE *ordersFile);
static void   readClients    (FILE *clientsFile);
static size_t readClient     (CLIENT *clientTemp,FILE *clientsFile);
static void   readOrders     (FILE *ordersFile);
static size_t readOrder      (ORDER *orderTemp,FILE *ordersFile);

/**
 * Creates and overrides new files
 */
void newFile(void){
  if(canDeleteFiles()){
    //opens the files in write mode, thus overriding them with nothing
    FILE *clients = fopen("in/binStructures/clients.bin","wb");
    FILE *books   = fopen("in/binStructures/books.bin"  ,"wb");
    FILE *orders  = fopen("in/binStructures/orders.bin" ,"wb");
    //check for file opening errors
    if(clients==NULL||books==NULL||orders==NULL){
      perror("\tERROR: There was an error opening the file! Aborting...");
      exit(FILE_ERROR);
    }
    //close files
    fclose(clients);
    fclose(books);
    fclose(orders);
    printf("\tAll information from the files removed with success!\n");
  }
  else{
    printf("\tACTION CANCELED: The files will be untouched!\n");
  }
}

/**
 * Checks if the user really wants to remove the information on the files
 * @return true to proceed and false to cancel
 */
static bool canDeleteFiles(void){
  char answer;
  printf("             Are you sure you want to delete the information on the files? (y/n)             \n");
  printf("                             (this action is non reverteable)             \n");
  printPrompt();
  scanf("%c",&answer);
  getchar();
  return answer=='y';
}

/**
 * Creates and overrides new dataStructures
 */
void newDataStructures(void){
  if(canDeleteDS()){
    freelinked(clientlist);
    freequeue(&orderQueue);
    clientlist=NULL;
    orderQueue=NULL;
    printf("\tProgram data structures' information removed with success!\n");
  }
  else{
    printf("\tACTION CANCELED: The program data structures will be untouched!\n");
  }  
}

/**
 * Checks if the user really wants to remove the information on the data structures
 * @return true to proceed and false to cancel
 */
static bool canDeleteDS(void){
  char answer;
  printf("             Are you sure you want to delete the information on the data structures? (y/n)             \n");
  printf("                                   (this action is non reverteable)             \n");
  printPrompt();
  scanf("%c",&answer);
  getchar();
  return answer=='y';
}

/**
 * Writes the client's linked list to a file
 * @param *clientsFile the clients' file
 */
static void writeClients(FILE *clientsFile){
  clientNODE *clientlistTemp=clientlist;
  while(clientlistTemp!=NULL){
    writeClient(clientlistTemp,clientsFile);
    clientlistTemp=clientlistTemp->next;
  }
}

/**
 * Writes a client to a file
 * @param *client the client to write to the file
 * @param *clientsFile the clients' file
 */
static void writeClient(const clientNODE *client,FILE *clientsFile){
  //write the actual client
  fwrite(&(client->data),sizeof(CLIENT),1,clientsFile);
  //write the orders' array of the client
  if(client->data.orders!=NULL){
    fwrite(client->data.orders,sizeof(ORDER),client->data.numOfOrders,clientsFile);
  }  
}

/**
 * Writes the orders' queue to a file
 * @param *ordersFile the orders' file
 */
static void writeOrders(FILE *ordersFile){
  ORDER_NODE_QUEUE *orderQueueTemp=NULL;
  //write the whole queue to the file and to a temporary queue
  while(orderQueue!=NULL){
    writeOrder(&orderQueueTemp,ordersFile);
  }
  //write the queue back to the original queue
  orderQueue=orderQueueTemp;
}

/**
 * Writes an order to a file
 * @param *ordersTemp the order to write to the file
 * @param *ordersFile the orders' file
 */
static void writeOrder(ORDER_NODE_QUEUE **ordersTemp,FILE *ordersFile){
  //take the order out of the original queue and write it
  ORDER orderToInsert=dequeue(&orderQueue);
  fwrite(&orderToInsert,sizeof(ORDER),1,ordersFile);
  //add the order to the temporary queue
  if(isemptyqueue(*ordersTemp)){
    *ordersTemp=createqueue(orderToInsert);
  }
  else{
    enqueue(ordersTemp,orderToInsert);
  } 
}

/**
 * Reads the clients from the file
 * @param *clientsFile the clients' file
 */
static void readClients(FILE *clientsFile){
  CLIENT clientTemp;
  while(readClient(&clientTemp,clientsFile)){
    //add the read client to its linked list
    if(isemptylist(clientlist)){
      clientlist=createLinked(clientTemp);
    }
    else{
      eappendlinked(clientlist,clientTemp);
    }
  }
}

/**
 * Reads a client from the file
 * @param *clientTemp the read client
 * @param *clientsFile the clients' file
 * @return the output of fread on a single client
 */
static size_t readClient(CLIENT *clientTemp,FILE *clientsFile){
  size_t elementsRead=fread(clientTemp,sizeof(CLIENT),1,clientsFile);
  if(clientTemp->numOfOrders!=0){
    clientTemp->orders=memalloc(clientTemp->numOfOrders*sizeof(ORDER));
    for(size_t i=0;i<clientTemp->numOfOrders;i++){
      fread(&((*clientTemp).orders[i]),sizeof(ORDER),1,clientsFile);
    }
  }
  return elementsRead;
}

/**
 * Reads the orders from the file
 * @param *ordersFile the orders' file
 */
static void readOrders(FILE *ordersFile){
  ORDER orderTemp;
  while(readOrder(&orderTemp,ordersFile)){
    //add the read order to its queue
    if(isemptyqueue(orderQueue)){
      orderQueue=createqueue(orderTemp);
    }
    else{
      enqueue(&orderQueue,orderTemp);
    }
  }
}

/**
 * Reads an order from the file
 * @param *orderTemp the read order
 * @param *ordersFile the orders' file
 * @return the output of fread on a single order
 */
static size_t readOrder(ORDER *orderTemp,FILE *ordersFile){
  return fread(orderTemp,sizeof(ORDER),1,ordersFile);
}

/**
 * Saves the contents of the three structures of the program into their respective files
 */
void saveFile(void){
  //will empty the files, and write the current contents of the data structures
  FILE *clients = fopen("in/binStructures/clients.bin","wb+");
  FILE *books   = fopen("in/binStructures/books.bin","wb+");
  FILE *orders  = fopen("in/binStructures/orders.bin","wb+");
  if(clients==NULL||books==NULL||orders==NULL){
    perror("\tERROR: There was an error opening the file! Aborting...");
    exit(FILE_ERROR);
  }
  writeClients(clients);
  writeOrders(orders);
  fclose(clients);
  fclose(books);
  fclose(orders);
  printf("\tInformation saved on the files successfully!\n");
}

/**
 * Opens the contents of the three structures on the files to their respective structures
 */
void openFile(void){
  //empty the existing data structures
  newDataStructures();
  FILE *clients = fopen("in/binStructures/clients.bin","rb");
  FILE *books   = fopen("in/binStructures/books.bin","rb");
  FILE *orders  = fopen("in/binStructures/orders.bin","rb");
  if(clients==NULL||books==NULL||orders==NULL){
    perror("\tERROR: There was an error opening the file! Aborting...");
    exit(FILE_ERROR);
  }
  readClients(clients);
  readOrders(orders);
  fclose(clients);
  fclose(books);
  fclose(orders);
  printf("\tInformation from the files opened successfully!\n");
}