//global includes
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
//project includes
#include"mem.h"
#include"clientOperations.h"
#include"client.h"
#include"orderOperations.h"
#include"order.h"
//global variables
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;
static const char *dateSeparator="-";


static void updateClientOrders(uint32_t NIF,ORDER order){
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
 * Creates a new order
 * @return the new order
 */
ORDER newOrder(void){
  //hold input info
  uint32_t ISBN,NIF;
  char date[11];
  uint16_t quantity;
  double totalPrice;
  //header
  printf("=======================================\n");
  printf("     ========= NEW ORDER =========     \n");
  //NIF input
  while(true){
    NIF=getNIF();
    if(!lsearchlinked(clientlist,NIF)){
      fprintf(stderr,"The NIF you entered is not on the system. Please insert a correct NIF.\n");
    }
    else{
      break;
    }
  }
  //ISBN input
  //TODO: correct ISBN
  ISBN=1234567;
  //date input
  getDate(date);
  //quantity input
  //TODO: check if correct quantity
  quantity=getQuantity();
  //totalPrice input
  //TODO: update totalPrice
  totalPrice=100.5;
  //footer
  printf("=========================================\n");
  //create order
  ORDER order={.ISBN=ISBN,.NIF=NIF,.quantity=quantity,.totalPrice=totalPrice};
  strcpy(order.date,date);
  //update the client with the specified NIF's orders
  updateClientOrders(NIF,order);
  return order;
}

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
 * Asks the order's date
 * @return the date
 */
void getDate(char *date){
  char dayTemp[255],monthTemp[255],yearTemp[255];
  uint8_t day,month;
  uint16_t year;
  time_t currTime = time(NULL);
  struct tm tm = *localtime(&currTime);
  //ask the year
  while(true){
    //header
    printf("            What's the year?            \n");
    //get year input
    if(fgets(yearTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the year!");
      }
      strcpy(yearTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      yearTemp[strcspn(yearTemp,"\n")]=0;
      for(size_t i=0;i<strlen(yearTemp);i++){
        if(!isdigit(yearTemp[i])){
          fprintf(stderr,"ERROR: The year must be a positive number!\n");
          goto YEARNUMBERLABEL;
        }
      }
      sscanf(yearTemp,"%"SCNu16,&year);
      if(year>tm.tm_year+1900){
        fprintf(stderr,"ERROR: The year is invalid\n");
        continue;
      }
      break;
      YEARNUMBERLABEL:
      continue;
    }
  }
  //ask the month
  while(true){
    //header
    printf("            What's the month?            \n");
    //get month input
    if(fgets(monthTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the month!");
      }
      strcpy(monthTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      monthTemp[strcspn(monthTemp,"\n")]=0;
      for(size_t i=0;i<strlen(monthTemp);i++){
        if(!isdigit(monthTemp[i])){
          fprintf(stderr,"ERROR: The month must be a positive number!\n");
          goto MONTHNUMBERLABEL;
        }
      }
      sscanf(monthTemp,"%"SCNu8,&month);
      if(month<1||month>12){
        fprintf(stderr,"ERROR: The month is invalid\n");
        continue;
      }
      break;
      MONTHNUMBERLABEL:
      continue;
    }
  }
  const uint8_t MAX_DAY=getLastDayOfMonth(month,year);
  //ask the day
  while(true){
    //header
    printf("            What's the day?            \n");
    //get day input
    if(fgets(dayTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the day!");
      }
      strcpy(dayTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      dayTemp[strcspn(dayTemp,"\n")]=0;
      for(size_t i=0;i<strlen(dayTemp);i++){
        if(!isdigit(dayTemp[i])){
          fprintf(stderr,"ERROR: The day must be a positive number!\n");
          goto DAYNUMBERLABEL;
        }
      }
      sscanf(dayTemp,"%"SCNu8,&day);
      if(day<1||day>MAX_DAY){
        fprintf(stderr,"ERROR: The day is invalid\n");
        continue;
      }
      break;
      DAYNUMBERLABEL:
      continue;
    }
  }
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
 * Asks the order's quantity
 * @return the quantity
 */
uint16_t getQuantity(void){
  char quantityTemp[5];
  uint16_t quantity;
  while(true){
    //header
    printf("            What's the quantity?            \n");
    //get quantity input
    if(fgets(quantityTemp,5,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the quantity!");
      }
      strcpy(quantityTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      quantityTemp[strcspn(quantityTemp,"\n")]=0;
      for(size_t i=0;i<strlen(quantityTemp);i++){
        if(!isdigit(quantityTemp[i])){
          fprintf(stderr,"ERROR: The quantity must be a number!\n");
          goto QUANTITYNUMBERLABEL;
        }
      }
      sscanf(quantityTemp,"%"SCNu16,&quantity);
      //check quantity according to ISBN
      break;
      QUANTITYNUMBERLABEL:
      continue;
    }
  }
  return quantity;
}

/**
 * Checks if both orders are equal
 * @param order1 used to compare with order2
 * @param order2 used to compare with order1
 * @return true if they're equal or false otherwise
 */
bool isSameOrder(ORDER order1,ORDER order2){
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
void printOrder(ORDER order,size_t orderNum){
  printf("============ORDER %zu============\n",orderNum+1);
  printf("\tISBN:%"PRIu32"\n",order.ISBN);
  printf("\tNIF:%"PRIu32"\n",order.NIF);
  printf("\tDATE:%s\n",order.date);
  printf("\tQuantity:%"PRIu16"\n",order.quantity);
  printf("\ttotalPrice:%lf\n",order.totalPrice);
  printf("===============================\n");
}