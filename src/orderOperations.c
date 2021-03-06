//global includes
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
//project includes
#include"librorithm.h"
#include"mem.h"
#include"clientOperations.h"
#include"client.h"
#include"orderOperations.h"
#include"order.h"
#include"booksOperations.h"
//global variables
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;
extern PNodoAB Books;
static const char *dateSeparator="-";
//static function prototypes
static void printContainerOrders(const size_t type);
static ORDER buildOrder(const uint32_t NIF,const long int ISBN,const uint16_t quantity,const double totalPrice,const char *date);
static uint8_t getLastDayOfMonth(const uint8_t month,const uint16_t year);

/**
 * Creates a new order
 * @return the new order
 */
ORDER newOrder(void){
  //hold input info
  long int ISBN;
  uint32_t NIF;
  char date[11];
  uint16_t quantity;
  double totalPrice;
  //header
  printContainerOrders(1);
  //NIF input
  while(true){
    if(!getNIF(&NIF)){
      fprintf(stderr,"\tACTION CANCELED: No order was added!\n");
      return (ORDER){.NIF=0};
    }
    else if(!lsearchlinked(clientlist,NIF)){
      fprintf(stderr,"The NIF you entered is not on the system. Please insert a correct NIF.\n");
    }
    else{
      break;
    }
  }
  //ISBN input
  while(true){
    if(!getISBN(&ISBN)){
      fprintf(stderr,"\tACTION CANCELED: No order was added!\n");
      return (ORDER){.NIF=0};
    }
    else if(!PesquisarABP(Books,(LIVRO){.ISBN=ISBN})){
      fprintf(stderr,"\tERROR: There are no books with the specified ISBN!\n");
      continue; 
    }
    else if(getBookQuantity(Books,ISBN)<1){
      fprintf(stderr,"\tERROR: There aren't any books with that ISBN in stock!\n");
      continue;  
    }
    else{
      break;
    }
  }
  //date input
  getDate(date);
  //quantity input
  if(!getQuantity(&quantity,ISBN)){
    fprintf(stderr,"\tACTION CANCELED: No order was added!\n");
    return (ORDER){.NIF=0};  
  }
  //totalPrice input
  totalPrice=quantity*(double)getBookPrice(Books,ISBN);
  //footer
  printContainerOrders(2);
  //update book quantity
  setBookQuantity(Books,ISBN,quantity);
  //create order and return
  return buildOrder(NIF,ISBN,quantity,totalPrice,date);
}

/**
 * Prints a container
 * @param type the type of the container (1:Header,2:Footer)
 */
static void printContainerOrders(const size_t type){
  if(type==1){
    printf("=======================================\n");
    printf("     ========= NEW ORDER =========     \n"); 
  }
  else if(type==2){
    printf("=======================================\n");
  }
}

/**
 * Builds and returns the order
 * @param NIF the client's NIF
 * @param ISBN book's ISBN
 * @param quantity the book quantity
 * @param totalPrice the updated total price of the order
 * @param *date the order's date
 * @return the new order
 */
static ORDER buildOrder(const uint32_t NIF,const long int ISBN,const uint16_t quantity,const double totalPrice,const char *date){
  ORDER order={.ISBN=ISBN,.NIF=NIF,.quantity=quantity,.totalPrice=totalPrice};
  strcpy(order.date,date);
  return order; 
}

/**
 * Updates the clients' orders
 * @param NIF the NIF of the client to be updated
 * @param order the ORDER array to be updated
 */
void updateClientOrders(uint32_t NIF,ORDER order){
  clientNODE *clientToChange=getSearchlinked(clientlist,NIF);
  if(clientToChange->data.orders==NULL){
    clientToChange->data.numOfOrders=1;
    clientToChange->data.orders=memalloc(sizeof(ORDER));
  }
  else{
    clientToChange->data.numOfOrders++;
    clientToChange->data.orders=memrealloc(clientToChange->data.orders,clientToChange->data.numOfOrders*sizeof(ORDER));  
  }
  (clientToChange->data.orders)[clientToChange->data.numOfOrders-1]=order;  
}



/**
 * Asks the order's date
 * @return the date
 */
void getDate(char *date){
  char dayTemp[255],monthTemp[255],yearTemp[255];
  uint8_t day,month;
  uint16_t year;
  //ask the year
  getYear(yearTemp,&year);
  //ask the month
  getMonth(monthTemp,&month);
  //get last day of month
  const uint8_t MAX_DAY=getLastDayOfMonth(month,year);
  //ask the day
  getDay(dayTemp,&day,MAX_DAY);
  //copy to date
  if(strlen(dayTemp)==1){
    strcpy(date,"0");
    strcat(date,dayTemp);  
  }
  else{ 
    strcpy(date,dayTemp);
  }
  strcat(date,dateSeparator);
  if(strlen(monthTemp)==1){
    strcat(date,"0");  
    strcat(date,monthTemp);  
  }
  else{ 
    strcat(date,monthTemp);
  }
  strcat(date,dateSeparator);
  strcat(date,yearTemp);
}

/**
 * Gets the year
 * @param *yearTemp the year asked as a string
 * @param *year the year asked
 */
void getYear(char *yearTemp,uint16_t *year){
  time_t currTime = time(NULL);
  struct tm tm = *localtime(&currTime);
  while(true){
    //header
    printf("            What's the year?            \n");
    printPrompt();
    //get year input
    if(fgets(yearTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the year!");
      }
      strcpy(yearTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      yearTemp[strcspn(yearTemp,"\n")]=0;
      for(size_t i=0;i<strlen(yearTemp);i++){
        if(!isdigit(yearTemp[i])){
          fprintf(stderr,"\tERROR: The year must be a positive number!\n");
          goto YEARNUMBERLABEL;
        }
      }
      sscanf(yearTemp,"%"SCNu16,year);
      if(*year>tm.tm_year+1900){
        fprintf(stderr,"\tERROR: The year is invalid\n");
        continue;
      }
      break;
      YEARNUMBERLABEL:
      continue;
    }
  }
}

/**
 * Gets the month
 * @param *monthTemp the month asked as a string
 * @param *month the month asked
 */
void getMonth(char *monthTemp,uint8_t *month){
  while(true){
    //header
    printf("            What's the month?            \n");
    printPrompt();
    //get month input
    if(fgets(monthTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the month!");
      }
      strcpy(monthTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      monthTemp[strcspn(monthTemp,"\n")]=0;
      for(size_t i=0;i<strlen(monthTemp);i++){
        if(!isdigit(monthTemp[i])){
          fprintf(stderr,"\tERROR: The month must be a positive number!\n");
          goto MONTHNUMBERLABEL;
        }
      }
      sscanf(monthTemp,"%"SCNu8,month);
      if(*month<1||*month>12){
        fprintf(stderr,"\tERROR: The month is invalid\n");
        continue;
      }
      break;
      MONTHNUMBERLABEL:
      continue;
    }
  }
}

/**
 * Gets the day
 * @param *dayTemp the day asked as a string
 * @param *day the day asked
 * @param MAX_DAY the maximum day for the specified month
 */
void getDay(char *dayTemp,uint8_t *day,const uint8_t MAX_DAY){
  while(true){
    //header
    printf("            What's the day?            \n");
    printPrompt();
    //get day input
    if(fgets(dayTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the day!");
      }
      strcpy(dayTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      dayTemp[strcspn(dayTemp,"\n")]=0;
      for(size_t i=0;i<strlen(dayTemp);i++){
        if(!isdigit(dayTemp[i])){
          fprintf(stderr,"\tERROR: The day must be a positive number!\n");
          goto DAYNUMBERLABEL;
        }
      }
      sscanf(dayTemp,"%"SCNu8,day);
      if(*day<1||*day>MAX_DAY){
        fprintf(stderr,"\tERROR: The day is invalid\n");
        continue;
      }
      break;
      DAYNUMBERLABEL:
      continue;
    }
  }
}

/**
 * Gets the last day of the month for the specified month
 * @param month the specified month
 * @param year the specified year (needed for leap year calculations)
 * @return the last day of the month
 */
static uint8_t getLastDayOfMonth(const uint8_t month,const uint16_t year){
  if(month<8){
    if(month==2){
      return (year%4==0&&year%100!=0)||year%400==0?29:28;
    }
    else{
      return (month&1)==1?31:30;
    }
  }
  else{
    return (month&1)==1?30:31;  
  }
}

/**
 * Asks the order's quantity
 * @param *quantity the new quantity
 * @param ISBN the ISBN to search the quantity
 * @return true if the quantity was asked successfully and false if it was canceled
 */
bool getQuantity(uint16_t *quantity,long int ISBN){
  char quantityTemp[5];
  while(true){
    //header
    printf("            What's the quantity? (0 to CANCEL)            \n");
    printPrompt();
    //get quantity input
    if(fgets(quantityTemp,5,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the quantity!");
      }
      strcpy(quantityTemp,"");
      continue;
    }
    else{
      if(strlen(quantityTemp)==2&&quantityTemp[0]=='0'){
        return false;
      }
      //remove newline and verify input
      quantityTemp[strcspn(quantityTemp,"\n")]=0;
      for(size_t i=0;i<strlen(quantityTemp);i++){
        if(!isdigit(quantityTemp[i])){
          fprintf(stderr,"\tERROR: The quantity must be a positive number!\n");
          goto QUANTITYNUMBERLABEL;
        }
      }
      sscanf(quantityTemp,"%"SCNu16,quantity);
      if(*quantity<1||*quantity>getBookQuantity(Books,ISBN)){
        fprintf(stderr,"\tERROR: There aren't enough books in stock for that amount!\n");
        continue;
      }
      break;
      QUANTITYNUMBERLABEL:
      continue;
    }
  }
  return true;
}

/**
 * Checks if both orders are equal
 * @param order1 used to compare with order2
 * @param order2 used to compare with order1
 * @return true if they're equal or false otherwise
 */
bool isSameOrder(const ORDER order1,const ORDER order2){
  return 
  order1.ISBN==order2.ISBN&&
  order1.NIF==order2.NIF&&
  strcmp(order1.date,order2.date)==0&&
  order1.quantity==order2.quantity&&
  order1.NIF==order2.NIF;
}

/**
 * Prints an order
 * @param order the order to print
 * @param orderNum the index of the order in the client's list
 */
void printOrder(const ORDER order,const size_t orderNum){
  printf("============ORDER %zu============\n",orderNum+1);
  printf("\tISBN:%ld\n",order.ISBN);
  printf("\tNIF:%"PRIu32"\n",order.NIF);
  printf("\tDATE:%s\n",order.date);
  printf("\tQuantity:%"PRIu16"\n",order.quantity);
  printf("\tTotal Price:%.2lf\n",order.totalPrice);
  printf("===============================\n");
}