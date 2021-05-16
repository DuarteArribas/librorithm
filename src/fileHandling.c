//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<sys/stat.h>
//project includes
#include"fileHandling.h"
#include"librorithm.h"
#include"mem.h"
#include"client.h"
#include"order.h"
#include"books.h"
#include"booksOperations.h"
//global variables
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;
extern PNodoAB Books;
//static function prototypes
static bool   canDeleteFiles (void);
static bool   canDeleteDS    (void);
static void   writeClients   (FILE *clients);
static void   writeClient    (const clientNODE *client,FILE *clientsFile);
static void   writeOrders    (FILE *ordersFile);
static void   writeOrder     (ORDER_NODE_QUEUE **ordersTemp,FILE *ordersFile);
static void   writeBooks     (const PNodoAB Books,FILE *booksFile);
static void   readClients    (FILE *clientsFile);
static size_t readClient     (CLIENT *clientTemp,FILE *clientsFile);
static void   readOrders     (FILE *ordersFile);
static size_t readOrder      (ORDER *orderTemp,FILE *ordersFile);
static void   readBooks      (FILE *booksFile);
static size_t readBook       (LIVRO *X,FILE *booksFile);

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
    Books=DestruirAB(Books);
    Books=CriarAB();
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
 * Writes the books' to a file
 * @param Books the books in the tree
 * @param *booksFile the books' file
 */
static void writeBooks(const PNodoAB T,FILE *booksFile){
  if(T==NULL){
    return;
  }
  fwrite(&(T->Elemento), sizeof(LIVRO), 1, booksFile);
  writeBooks(T->Direita, booksFile);
  writeBooks(T->Esquerda, booksFile);
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
 * Reads the books from the file
 * @param *booksFile the books' file
 */
static void readBooks(FILE *booksFile){
  LIVRO temp;
  while(readBook(&temp,booksFile)){
    Books=InserirABP(Books, temp);
    if(verificarEquilibrio(Books)==0){
      Books=CriarABPEquilibradaIB(Books);
    }
  }
}

/**
 * Reads an books from the file
 * @param *X the read book
 * @param *booksFile the books' file
 * @return the output of fread on a single book
 */
static size_t readBook(LIVRO *X,FILE *booksFile){
  return fread(X,sizeof(LIVRO),1,booksFile);
}


/**
 * Saves the contents of the three structures of the program into their respective files
 */
void saveFile(void){
  //empty the existing files
  newFile();
  FILE *clients = fopen("in/binStructures/clients.bin","wb+");
  FILE *books   = fopen("in/binStructures/books.bin","wb+");
  FILE *orders  = fopen("in/binStructures/orders.bin","wb+");
  if(clients==NULL||books==NULL||orders==NULL){
    perror("\tERROR: There was an error opening the file! Aborting...");
    exit(FILE_ERROR);
  }
  writeClients(clients);
  writeOrders(orders);
  writeBooks(Books,books);
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
  //check if files are empty
  bool filesSaved[3]={false,false,false};
  struct stat buffer;
  fstat(fileno(clients),&buffer);
  if(buffer.st_size==0){
    fprintf(stderr,"\tERROR: No data has been found for clients!\n");
  }
  else{
    readClients(clients);
    filesSaved[0]=true;
  }
  fstat(fileno(books),&buffer);
  if(buffer.st_size==0){
    fprintf(stderr,"\tERROR: No data has been found for books!\n");
  }
  else{
    readBooks(books);
    filesSaved[1]=true;
  }
  fstat(fileno(orders),&buffer);
  if(buffer.st_size==0){
    fprintf(stderr,"\tERROR: No data has been found for orders!\n");
  }
  else{
    readOrders(orders);
    filesSaved[2]=true;
  }
  fclose(clients);
  fclose(books);
  fclose(orders);
  if(filesSaved[0]||filesSaved[1]||filesSaved[2]){
    printf("\tInformation from the {\n");
    if(filesSaved[0]){
      printf("\t\tclients,\n");
    }
    if(filesSaved[1]){
      printf("\t\tbooks,\n");
    }
    if(filesSaved[2]){
      printf("\t\torders,\n");
    }
    printf("\t} files opened successfully!\n");
  }
  else{
    fprintf(stderr,"\tERROR: No information was opened!\n");  
  }
}