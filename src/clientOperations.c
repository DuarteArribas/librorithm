//global includes
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
//project includes
#include"librorithm.h"
#include"orderOperations.h"
#include"clientOperations.h"
#include"client.h"
//global variables
extern clientNODE *clientlist;
static const char *plus="+";
//static function prototypes
static void   printContainer         (const size_t type);
static bool   getUniqueNIF           (uint32_t *NIF);
static CLIENT buildClient            (const uint32_t NIF,const char *name,const char *address,const char *phoneNumber);
static void   printRegularProperties (const CLIENT client);
static bool   canShowOrders          (void);
static void   showOrders             (const CLIENT client);

/**
 * Creates a new client
 * @return the new client
 */
CLIENT newClient(void){
  //hold input info
  uint32_t NIF;
  char name[255],address[255],phoneNumber[18];
  //header
  printContainer(HEADER);
  //input and validation
  if(!getUniqueNIF(&NIF)||!getName(name)||!getAddress(address)||!getPhoneNumber(phoneNumber)){
    fprintf(stderr,"\tACTION CANCELED: No user was created!\n");
    return (CLIENT){.NIF=0};
  }
  //footer
  printContainer(FOOTER);
  //create and return client
  return buildClient(NIF,name,address,phoneNumber);
}

/**
 * Prints a container
 * @param type the type of the container (1:Header,2:Footer)
 */
static void printContainer(const size_t type){
  if(type==1){
    printf("=========================================\n");
    printf("      ========= NEW CLIENT =========     \n");  
  }
  else if(type==2){
    printf("=========================================\n");
  }
}

/**
 * Gets a unique NIF
 * @param *NIF the unique NIF
 * @return true if the NIF was asked successfully and false if it was canceled
 */
static bool getUniqueNIF(uint32_t *NIF){
  while(true){
    if(!getNIF(NIF)){
      return false;
    }
    if(lsearchlinked(clientlist,*NIF)){
      fprintf(stderr,"\tThe NIF you entered is not unique, which might mean the user is already on the system.\n");
    }
    else{
      return true;
    }
  }
}

/**
 * Builds and returns the client
 * @param NIF the client's NIF
 * @param *name the client's name
 * @param *address the client's address
 * @param *phoneNumber the client's phone number
 * @return the new client
 */
static CLIENT buildClient(const uint32_t NIF,const char *name,const char *address,const char *phoneNumber){
  CLIENT client={.NIF=NIF,.numOfOrders=0,.orders=NULL};
  strcpy(client.name,name);
  strcpy(client.address,address);
  strcpy(client.phoneNumber,phoneNumber);
  return client;
}

/**
 * Ask the user's NIF
 * @param *NIF the user's NIF
 * @return true if the NIF was asked successfully and false if it was canceled
 */
bool getNIF(uint32_t *NIF){
  char NIFtemp[100];
  while(true){
    //header
    printf("     What's the NIF? (0 to CANCEL)     \n");
    printPrompt();
    //get NIF input
    if(fgets(NIFtemp,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the NIF!");
      }
      strcpy(NIFtemp,"");
      continue;
    }
    if(strlen(NIFtemp)==2&&NIFtemp[0]=='0'){
      return false;
    }
    //check if NIF is a string
    for(size_t i=0;i<strlen(NIFtemp)-1;i++){
      if(!isdigit(NIFtemp[i])){
        fprintf(stderr,"\tERROR: The NIF must be a number!\n");
        goto NIFNUMBERLABEL;
      }
    }
    //transform NIF into integer
    sscanf(NIFtemp,"%"SCNu32,NIF);
    //verify input
    if(strlen(NIFtemp)-1!=9){
      fprintf(stderr,"\tERROR: The NIF must be a 9 digit number!\n");
      NIFNUMBERLABEL:
      strcpy(NIFtemp,"");
      continue;
    }
    else{
      return true;
    }
  }
}

/**
 * Ask the user's new NIF to change
 * @param *NIF will store the new NIF or 1 to stay as is
 * @param oldNIF the old NIF to compare
 * @return true if the NIF was asked successfully and false if it was canceled
 */
bool getNIFChange(uint32_t *NIF,uint32_t oldNIF){
  char NIFtemp[100];
  while(true){
    //header
    printf("     What's the new NIF? (0 to CANCEL)     \n");
    printPrompt();
    //get NIF input
    if(fgets(NIFtemp,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the NIF!");
      }
      strcpy(NIFtemp,"");
      continue;
    }
    if(strlen(NIFtemp)==2&&NIFtemp[0]=='0'){
      return false;
    }
    if(NIFtemp[0]=='-'&&NIFtemp[1]=='1'){
      *NIF=1;
      return true;
    }
    //check if NIF is a string
    for(size_t i=0;i<strlen(NIFtemp)-1;i++){
      if(!isdigit(NIFtemp[i])){
        fprintf(stderr,"\tERROR: The NIF must be a number!\n");
        goto NIFNUMBERLABEL;
      }
    }
    //transform NIF into integer
    sscanf(NIFtemp,"%"SCNu32,NIF);
    //verify input
    if(strlen(NIFtemp)-1!=9){
      fprintf(stderr,"\tERROR: The NIF must be a 9 digit number!\n");
      NIFNUMBERLABEL:
      strcpy(NIFtemp,"");
      continue;
    }
    else if(lsearchlinked(clientlist,*NIF)&&*NIF!=oldNIF){
      fprintf(stderr,"\tThe NIF you entered is not unique, which might mean the user is already on the system.\n");
      continue;
    }
    else{
      return true;
    }
  }
}

/**
 * Asks the user's name
 * @param *name the user's name
 * @return true if the name was asked successfully and false if it was canceled
 */
bool getName(char *name){
  char nameTemp[255];
  while(true){
    //header
    printf("     What is the name? (0 to CANCEL)     \n");
    printPrompt();
    //get name input
    if(fgets(nameTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the name!");
      }
      strcpy(nameTemp,"");
      continue;
    }
    else{
      if(strlen(nameTemp)==2&&nameTemp[0]=='0'){
        return false;
      }
      //remove newline and verify input
      nameTemp[strcspn(nameTemp,"\n")]=0;
      strcpy(name,nameTemp);
      return true;
    }
  }
}

/**
 * Asks the user's address
 * @param *address the user's address
 * @return true if the address number was asked successfully and false if it was canceled
 */
bool getAddress(char *address){
  char addressTemp[255];
  while(true){
    printf("     What's the address? (0 to CANCEL)     \n");
    printPrompt();
    //get address input
    if(fgets(addressTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the address!");
      }
      strcpy(addressTemp,"");
      continue;
    }
    else{
      if(strlen(addressTemp)==2&&addressTemp[0]=='0'){
        return false;
      }
      //remove newline and verify input
      addressTemp[strcspn(addressTemp,"\n")]=0;
      strcpy(address,addressTemp);
      return true;
    }
  }
}

/**
 * Asks the user's phone number
 * @param *phoneNumber the user's phone number
 * @return true if the phone number was asked successfully and false if it was canceled
 */
bool getPhoneNumber(char *phoneNumber){
  char phoneTemp[100],country[100];
  while(true){
    printf("     What's the country? (0 to CANCEL)     \n");
    printPrompt();
    //get country input to check the phone code number
    if(fgets(country,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the country!");
      }
      strcpy(phoneTemp,"");
      strcpy(country,"");
      strcpy(phoneNumber,"");
      continue;
    }
    else{
      if(strlen(country)==2&&country[0]=='0'){
        return false;
      }
      //format country string
      country[strcspn(country,"\n")]=0;
      for(size_t i=0;i<strlen(country)-1;i++){
        country[i]=tolower(country[i]);
      }
      //check countries
      FILE *fileCountry=fopen("in/countries","r");
      if(fileCountry==NULL){
        perror("\tERROR: There was an error checking the countries!");
        strcpy(phoneTemp,"");
        strcpy(country,"");
        strcpy(phoneNumber,"");
        continue;
      }
      char temp[100],temp2[100];
      bool countryAvailable=false;
      //read countries and check if the specified country is a valid country
      while(fscanf(fileCountry,"%s %s",temp,temp2)==2){
        //format read country string
        for(size_t i=0;i<strlen(temp);i++){
          temp[i]=tolower(temp[i]);
        }
        //if the country exists, ask the phone number
        if(strcmp(country,temp)==0){
          countryAvailable=true;
          //add the country's phone code number to the phone number
          strcpy(phoneNumber,plus);
          strcat(phoneNumber,temp2);
          strcat(phoneNumber," ");
          printf("     What is the phone number? (0 to CANCEL)     \n");
          printPrompt();
          //get phone number input
          if(fgets(phoneTemp,100,stdin)==NULL){
            if(ferror(stdin)){
              perror("\tERROR: There was an error reading the phone number!");
            }
            strcpy(phoneTemp,"");
            strcpy(country,"");
            strcpy(phoneNumber,"");
            goto PHONE_ERROR_LABEL;
          }
          else{
            if(strlen(phoneTemp)==2&&phoneTemp[0]=='0'){
              return false;
            }
            //check if phone number is a string
            for(size_t i=0;i<strlen(phoneTemp)-1;i++){
              if(!isdigit(phoneTemp[i])){
                fprintf(stderr,"\tERROR: The Phone Number must be a number!\n");
                strcpy(phoneTemp,"");
                strcpy(country,"");
                strcpy(phoneNumber,"");
                goto PHONE_ERROR_LABEL;
              }
            }
            //verify input
            if(strlen(phoneTemp)-1!=9){
              strcpy(phoneTemp,"");
              strcpy(country,"");
              strcpy(phoneNumber,"");
              goto PHONE_ERROR_LABEL;
            }
            strcat(phoneNumber,phoneTemp);
          }
        }
      }
      if(!countryAvailable){
        fprintf(stderr,"\tERROR: The country is not correct!\n");
        PHONE_ERROR_LABEL:
        strcpy(phoneTemp,"");
        strcpy(country,"");
        strcpy(phoneNumber,"");
        continue;
      }
      return true;
    }
  }
}

/**
 * Asks the user's new phone number to change
 * @param *phoneNumber will store the new phone number or 1 to stay as is
 * @return true if the phone number was asked successfully and false if it was canceled
 */
bool getPhoneNumberChange(char *phoneNumber){
  char phoneTemp[100],country[100];
  while(true){
    printf("     What's the country? (0 to CANCEL)     \n");
    printPrompt();
    //get country input to check the phone code number
    if(fgets(country,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading the country!");
      }
      strcpy(phoneTemp,"");
      strcpy(country,"");
      strcpy(phoneNumber,"");
      continue;
    }
    else{
      if(strlen(country)==2&&country[0]=='0'){
        return false;
      }
      if(country[0]=='-'&&country[1]=='1'){
        phoneNumber[0]='-';
        phoneNumber[1]='1';
        return true;
      }
      //format country string
      country[strcspn(country,"\n")]=0;
      for(size_t i=0;i<strlen(country)-1;i++){
        country[i]=tolower(country[i]);
      }
      //check countries
      FILE *fileCountry=fopen("in/countries","r");
      if(fileCountry==NULL){
        perror("\tERROR: There was an error checking the countries!");
        strcpy(phoneTemp,"");
        strcpy(country,"");
        strcpy(phoneNumber,"");
        continue;
      }
      char temp[100],temp2[100];
      bool countryAvailable=false;
      //read countries and check if the specified country is a valid country
      while(fscanf(fileCountry,"%s %s",temp,temp2)==2){
        //format read country string
        for(size_t i=0;i<strlen(temp);i++){
          temp[i]=tolower(temp[i]);
        }
        //if the country exists, ask the phone number
        if(strcmp(country,temp)==0){
          countryAvailable=true;
          //add the country's phone code number to the phone number
          strcpy(phoneNumber,plus);
          strcat(phoneNumber,temp2);
          strcat(phoneNumber," ");
          printf("     What is the phone number? (0 to CANCEL)     \n");
          printPrompt();
          //get phone number input
          if(fgets(phoneTemp,100,stdin)==NULL){
            if(ferror(stdin)){
              perror("\tERROR: There was an error reading the phone number!");
            }
            strcpy(phoneTemp,"");
            strcpy(country,"");
            strcpy(phoneNumber,"");
            goto PHONE_ERROR_LABEL;
          }
          else{
            if(strlen(phoneTemp)==2&&phoneTemp[0]=='0'){
              return false;
            }
            //check if phone number is a string
            for(size_t i=0;i<strlen(phoneTemp)-1;i++){
              if(!isdigit(phoneTemp[i])){
                fprintf(stderr,"\tERROR: The Phone Number must be a number!\n");
                strcpy(phoneTemp,"");
                strcpy(country,"");
                strcpy(phoneNumber,"");
                goto PHONE_ERROR_LABEL;
              }
            }
            //verify input
            if(strlen(phoneTemp)-1!=9){
              strcpy(phoneTemp,"");
              strcpy(country,"");
              strcpy(phoneNumber,"");
              goto PHONE_ERROR_LABEL;
            }
            strcat(phoneNumber,phoneTemp);
          }
        }
      }
      if(!countryAvailable){
        fprintf(stderr,"\tERROR: The country is not correct!\n");
        PHONE_ERROR_LABEL:
        strcpy(phoneTemp,"");
        strcpy(country,"");
        strcpy(phoneNumber,"");
        continue;
      }
      return true;
    }
  }
}


/**
 * Checks whether or not the user wants to check the user's orders
 * @return true if yes and false if no
 */
static bool canShowOrders(void){
  char checkOrders[255];
  while(true){
    //print show orders
    printf("  == Do you want to see the orders (y/n)? ==  \n");
    printPrompt();
    //get orders input
    if(fgets(checkOrders,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("\tERROR: There was an error reading your answer!");
      }
      strcpy(checkOrders,"");
      continue;
    }
    else{
      //remove newline
      checkOrders[strcspn(checkOrders,"\n")]=0;
      //change the input to lowercase
      checkOrders[0]=tolower(checkOrders[0]);
      //validate input
      if(strlen(checkOrders)!=1||(checkOrders[0]!='y'&&checkOrders[0]!='n')){
        fprintf(stderr,"\tERROR: The answer must either by a `y` or a `n`!\n");
        continue;
      }
      break;
    }
  }
  return checkOrders[0]=='y';
}

/**
 * Prints the client's orders
 * @param clients the client to show the orders
 */
static void showOrders(const CLIENT client){
  if(client.numOfOrders==0){
    fprintf(stderr,"\tThere are no orders for this user!\n");
  }
  else{
    for(size_t i=0;i<client.numOfOrders;i++){
      printOrder(client.orders[i],i);
    }
  } 
}

/**
 * Prints a client's information
 * @param client the client to print
 */
void printClient(const CLIENT client){
  if(client.NIF==0){
    fprintf(stderr,"\tERROR: Client doesn't exist!\n");
    return;
  }
  printRegularProperties(client);
  if(client.numOfOrders!=0){
    if(canShowOrders()){
      showOrders(client);
    }
  }
  printf("        == PRESS ENTER TO EXIT ==    \n");
  printf("===========================================\n");
}

/**
 * Prints a client's information for purchases
 * @param client the client to print
 */
void printClientReverse(const CLIENT client){
  printRegularProperties(client);
  printf("        NUM PURCHASES: %zu            \n",client.numOfOrders); 
  printf("===========================================\n");
}

/**
 * Prints a client's regular properties
 * @param client the client to print
 */
static void printRegularProperties(const CLIENT client){
  printf("===========================================\n");
  printf("             -> %s                   \n",client.name);
  printf("                                     \n");
  printf("                 NIF: %"PRIu32"      \n",client.NIF);
  printf("             ADDRESS: %s             \n",client.address);
  printf("        PHONE NUMBER: %s             \n",client.phoneNumber);  
}

/**
 * Gets the day, month, and year from the given date string
 * @param *date the given date
 * @param *day the new day
 * @param *month the new month
 * @param *year the new year
 */
void getDayMonthYear(char *date,uint8_t *day,uint8_t *month,uint16_t *year){
  *day=((uint8_t)date[0]-48)*10+((uint8_t)date[1]-48);
  *month=((uint8_t)date[3]-48)*10+((uint8_t)date[4]-48);
  *year=0;
  for(size_t i=0;i<strlen(date)-6;i++){
    *year+=((uint16_t)date[i+6]-48)*(uint16_t)(pow(10,strlen(date)-7-i));
  }
}

/**
 * Compares date1 with date2
 * @param *date1 the first date
 * @param *date2 the second date
 * @return 1 if date1>date2, -1 if date1<date2, 0 if date1==date2
 */
int8_t compareDates(char *date1,char *date2){
  uint8_t day1,month1,day2,month2;
  uint16_t year1,year2;
  getDayMonthYear(date1,&day1,&month1,&year1);
  getDayMonthYear(date2,&day2,&month2,&year2);
  if(year1>year2){
    return 1;
  }
  else if(year1<year2){
    return -1;
  }
  else{
    if(month1>month2){
      return 1;
    }
    else if(month1<month2){
      return -1;
    }
    else{
      if(day1>day2){
        return 1;
      }
      else if(day1<day2){
        return -1;
      }
      else{
        return 0;
      }
    }
  }
}