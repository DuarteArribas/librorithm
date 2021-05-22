//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
//project includes
#include"mem.h"
#include"orderOperations.h"
#include"order.h"
#include"clientOperations.h"
#include"client.h"
#include"booksOperations.h"
//global variables
clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;
extern PNodoAB Books;
//static function prototypes
static void       printClientNumber (size_t *userCount);
static void       copylinkedlist    (clientNODE **dest,clientNODE *src);
static clientNODE *mergeHelper      (clientNODE *list1,clientNODE *list2);
static void       splitMerge        (clientNODE *src,clientNODE **front,clientNODE **back);
static void       mergeSort         (clientNODE **list);
static void       printReverse      (clientNODE *head);

/**
 * Creates a client linked list with the specified element
 * @param value the value to add to the head of the list
 * @return the address of the head
 */
clientNODE *createLinked(const CLIENT value){
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
 * Cleans the whole client's linked list, without clearing the client's orders, freeing the memory
 * @param *head the address of the head
 */
void freelinked2(clientNODE *head){
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
bool isemptylist(const clientNODE *head){
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
bool lsearchlinked(clientNODE *head,const uint32_t value){
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
clientNODE *getSearchlinked(clientNODE *head,const uint32_t value){
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
clientNODE *getSearchlinkedByOrder(clientNODE *head,const ORDER value,size_t *pos){
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
void changeClient(clientNODE *head,const CLIENT client){
  if(head==NULL){
    return;
  }
  uint32_t oldNIF=client.NIF;
  uint32_t newNIF;
  char newName[255],newAddress[255],newPhoneNumber[18];
  printf("=========================================\n");
  printf("     ========= CHANGE CLIENT =========    \n");
  printf("            (-1 to keep as is)    \n");
  if(!getNIFChange(&newNIF,client.NIF)||!getName(newName)||!getAddress(newAddress)||!getPhoneNumberChange(newPhoneNumber)){
    fprintf(stderr,"\tACTION CANCELED: No user was changed!\n");
    return;
  }
  replaceOrdersNIF(&orderQueue,oldNIF,newNIF);
  while(head!=NULL){
    if(head->data.NIF==client.NIF){
      if(newNIF!=1){
        head->data.NIF=newNIF;
      }
      if(!(newName[0]=='-'&&newName[1]=='1')){
        strcpy(head->data.name,newName);
      }
      if(!(newAddress[0]=='-'&&newAddress[1]=='1')){
        strcpy(head->data.address,newAddress);
      }
      if(!(newPhoneNumber[0]=='-'&&newPhoneNumber[1]=='1')){
        strcpy(head->data.phoneNumber,newPhoneNumber);
      }
      //return so that it's more efficient (doesn't have to keep searching for another NIF, as it's unique)
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
    fprintf(stderr,"\tERROR: There was an error removing the specified client!\n");
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
bool removeClient(clientNODE **head,const uint32_t NIF){
  removeOrdersWithNIF(&orderQueue,NIF);
  if(*head==NULL){
    return false;
  }
  size_t clientIndex=0;
  clientNODE *temp=*head;
  while(temp!=NULL){
    if(temp->data.NIF==NIF){
      removelinked(head,clientIndex);
      return true;
    }
    ++clientIndex;
    temp=temp->next;
  }
  return false;
}

/**
 * Consults the client with the specified NIF
 * @param *head the address of the head
 * @param NIF the NIF of the client to remove
 */
void consultClientNIF(clientNODE *head,const uint32_t NIF){
  if(head==NULL){
    fprintf(stderr,"\tERROR: There are no clients on the system!\n");
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
  fprintf(stderr,"\tERROR: There isn't a client with the specified NIF! Please try again.\n");
  return;
}

/**
 * Consults the client with the specified name
 * @param *head the address of the head
 * @param *name the name of the client to remove
 */
void consultClientName(clientNODE *head,const char *name){
  if(head==NULL){
    fprintf(stderr,"\tERROR: There are no clients on the system!\n");
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
  fprintf(stderr,"\tERROR: There isn't a client with the specified name! Please try again.\n");
  return;
}

/**
 * Consults the client with the specified address
 * @param *head the address of the head
 * @param *address the address of the client to remove
 */
void consultClientAddress(clientNODE *head,const char *address){
  if(head==NULL){
    fprintf(stderr,"\tERROR: There are no clients on the system!\n");
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
  fprintf(stderr,"\tERROR: There isn't a client with the specified address! Please try again.\n");
  return;
}

/**
 * Consults every client
 * @param *head the address of the head
 */
void consultAll(clientNODE *head){
  if(head==NULL){
    fprintf(stderr,"\tERROR: There are no clients on the system!\n");
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
 * Prints the client's number, according to their inserted order
 * @param *userCount the current user count
 */
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
 * Append element at the start of the client's linked list
 * @param **head the address of the address of the head
 * @param value the value to append
 */
void sappendlinked(clientNODE **head,const CLIENT value){
  if(*head==NULL){
    fprintf(stderr,"\tERROR: The list is empty!\n");
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
void eappendlinked(clientNODE *head,const CLIENT value){
  if(head==NULL){
    fprintf(stderr,"\tERROR: The list is empty!\n");
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
 * @return the memory wasted by the clients in bytes
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

/**
 * Copies a linked list to another linked list
 * @param **dest the destination address of the adress of its head
 * @param **src the source address of the adress of its head
 */
static void copylinkedlist(clientNODE **dest,clientNODE *src){
  if(src==NULL){
    *dest=NULL;
  }
  *dest=createLinked(src->data);
  src=src->next;
  while(src!=NULL){
    eappendlinked(*dest,src->data);
    src=src->next;
  }
}

/**
 * Helps in merging the left and right parts
 * @param *list1 the left list
 * @param *list2 the right list
 * @return the merged lists
 */
static clientNODE *mergeHelper(clientNODE* list1,clientNODE* list2){
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

/**
 * Splits the lists
 * @param *src the source list
 * @param **front address of the address of the front 
 * @param **back address of the address of the back 
 * @return the merged lists
 */
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

/**
 * Sorts the linked list through the merge sort algorithm
 * @param **list the address of the address of the head of the list
 */
static void mergeSort(clientNODE **list){
  clientNODE *head=*list;
  clientNODE *left;
  clientNODE *right;
  //base case
  if((head==NULL)||(head->next==NULL)){
    return;
  }
  //recursive
  splitMerge(head, &left, &right);
  mergeSort(&left);
  mergeSort(&right);
  *list=mergeHelper(left,right);
}

/**
 * Prints the linked list in reverse order
 * @param *head the address of the head
 */
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
  mergeSort(&clientTemp);
  printReverse(clientTemp);
  freelinked2(clientTemp);
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
size_t getNumOfBooks(const char *monthTemp,const char *yearTemp){
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
void latestDateByBook(const long int ISBN){
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
    fprintf(stderr,"\tERROR: There aren't any books ordered with that ISBN!\n");
  }
  else{
    printf("\t======= DATE: %s =======\n",maxDate);
  }
}

/**
 * Prints the number of books of a given client, given the NIF
 * @param NIF the specified NIF
 */
void numBooksByClient(const uint32_t NIF){
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
  printf("\t======= NUM OF BOOKS: %zu =======\n",numOfBooks);
}

/**
 * Prints the client that wasted more money in the specified date
 * @param month the specified month
 * @param year the specified year
 */
void clientThatWastedMore(const uint8_t month,const uint16_t year){
   clientNODE *clientTemp=clientlist;
   CLIENT client;
   double totalPrice=0,maxTotalPrice=-1;
   uint8_t currMonth,currDay;
   uint16_t currYear;
   bool entered=false;
   while(clientTemp!=NULL){
    entered=false;
    for(size_t i=0;i<clientTemp->data.numOfOrders;i++){
      getDayMonthYear(clientTemp->data.orders[i].date,&currDay,&currMonth,&currYear);
      if(currMonth==month&&currYear==year){
        entered=true;
        totalPrice+=clientTemp->data.orders[i].totalPrice;
      }
    }
    if(totalPrice>maxTotalPrice&&entered){
      maxTotalPrice=totalPrice;
      client=clientTemp->data;
    }
    totalPrice=0;
    clientTemp=clientTemp->next;
  }
  if((int)(fabs(maxTotalPrice)-1)==0){
    fprintf(stderr,"\tERROR: There aren't any clients that wasted money on that date!\n");
  }
  else{
    printf("%lf\n",maxTotalPrice);
    printClient(client);
  }
}

/**
 * Prints every character that starts with the specified character
 */
void clientsThatStartWithChar(void){
  char startingChar;
  printf("            What's the first character? (0 to CANCEL)            \n");
  scanf("%c",&startingChar);
  getchar();
  if(startingChar==0){
    fprintf(stderr,"\tACTION CANCELED: No users were shown!\n");
    return;
  }
  clientNODE *clientTemp=clientlist;
  bool noneFound=true;
  while(clientTemp!=NULL){
    if(tolower(clientTemp->data.name[0])==tolower(startingChar)){
      printClient(clientTemp->data);
      if(noneFound){noneFound=false;}
    }
    clientTemp=clientTemp->next;
  }
  if(noneFound){
    fprintf(stderr,"\tERROR: There are no clients with the specified character as their name's starting character!\n");
  }
}

/**
 * Searches the array for the given value. (long int version)
 * @param size the size of the array
 * @param *array the array to search
 * @param value the value to search for
 * @return the first index of value in the array or -1 if it doesn't exit
 */
int64_t lilsearch(size_t size,long int *array,long int value){
  for(size_t i=0;i<size;i++){
    if(array[i]==value){
      return i;
    }
  }
  return -1;
}

/**
 * Holds the ISBN and the number of bought books with it
 */
typedef struct BEST_SOLD{
  long int ISBN;
  size_t count; 
}BEST_SOLD;

/**
 * Sorts the array in ascending order by ISBN
 * @param size the size of the array
 * @param *array the array to sort
 */
void bestSoldisort(size_t size,BEST_SOLD *array){
  if(size==1){return;}
  register size_t currentIndex;
  BEST_SOLD temp;
  for(register size_t i=1;i<size;++i){
    currentIndex=i;
    for(register int64_t j=i-1;j>=0;--j){
      if(array[currentIndex].ISBN<array[j].ISBN){
        temp=array[j];
        array[j]=array[currentIndex];
        array[currentIndex]=temp;
        --currentIndex;
      }
      else{
        break;
      }
    }
  }
}

/**
 * Shows the `amount` best sold books
 * @param *clients the clients linked list
 * @param amount the amound of books to show
 */
void showBestSoldBooks(clientNODE *clients,const size_t amount){
  size_t alreadyMaxSize=1;
  long int *alreadyMax=memalloc(sizeof(long int));
  long int count=0,currISBN;
  clientNODE *clientlistTemp=clients;
  size_t bestSoldSize=1;
  BEST_SOLD *bestSoldArray=memalloc(sizeof(BEST_SOLD));
  while(true){
    currISBN=0;
    while(clientlistTemp!=NULL){
      for(size_t i=0;i<clientlistTemp->data.numOfOrders;i++){
        if(currISBN==0){
          if(lilsearch(alreadyMaxSize,alreadyMax,clientlistTemp->data.orders[i].ISBN)==-1){
            currISBN=clientlistTemp->data.orders[i].ISBN;
            alreadyMax[alreadyMaxSize-1]=currISBN;
            alreadyMaxSize++;
            alreadyMax=realloc(alreadyMax,alreadyMaxSize*sizeof(long int));
          }
        }
        if(clientlistTemp->data.orders[i].ISBN==currISBN){
          count+=clientlistTemp->data.orders[i].quantity;
        }
      }
      clientlistTemp=clientlistTemp->next;
    }
    bestSoldArray[bestSoldSize-1]=(BEST_SOLD){currISBN,count};
    if(currISBN==0){
      break;
    }
    else{
      count=0;
      bestSoldSize++;
      bestSoldArray=realloc(bestSoldArray,bestSoldSize*sizeof(BEST_SOLD));
      clientlistTemp=clients;
    }
  }
  bestSoldSize--;
  bestSoldArray=realloc(bestSoldArray,bestSoldSize*sizeof(BEST_SOLD));
  bestSoldisort(bestSoldSize,bestSoldArray);
  if(amount>bestSoldSize){
    for(size_t i=0;i<bestSoldSize;i++){
      PesquisarABPISBN(Books,bestSoldArray[i].ISBN);
    }  
  }
  else{
    for(size_t i=0;i<amount;i++){
      PesquisarABPISBN(Books,bestSoldArray[i].ISBN);
    }
  }
  clnmem(alreadyMax);
  clnmem(bestSoldArray);
}