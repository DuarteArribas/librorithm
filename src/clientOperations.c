//global includes
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
//project includes
#include"clientOperations.h"
#include"client.h"

//global variables
extern clientNODE *clientlist;
static char *plus="+";

CLIENT newClient(void){
  //hold input info
  uint32_t NIF;
  char name[255],address[255],phoneNumber[17];
  //header
  printf("=========================================\n");
  printf("      ========= NEW CLIENT =========     \n");
  //NIF input
  while(1){
    NIF=getNIF();
    if(lsearchlinked(clientlist,NIF)){
      fprintf(stderr,"The NIF you entered is not unique, which might mean the user is already on the system.\n");
    }
    else{
      break;
    }
  }
  //name input
  getName(name);
  //address input
  getAddress(address);
  //phone input
  getPhoneNumber(phoneNumber);
  //footer
  printf("=========================================\n");
  //create and return client
  CLIENT client;
  client.NIF=NIF;
  strcpy(client.name,name);
  strcpy(client.address,address);
  strcpy(client.phoneNumber,phoneNumber);
  return client;
}

uint32_t getNIF(void){
  uint32_t NIF;
  char NIFtemp[100];
  while(true){
    //header
    printf("             What's the NIF?             \n");
    //get NIF input
    if(fgets(NIFtemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the NIF!");
      }
      strcpy(NIFtemp,"");
      continue;
    }
    //check if NIF is a string
    for(size_t i=0;i<strlen(NIFtemp)-1;i++){
      if(!isdigit(NIFtemp[i])){
        fprintf(stderr,"ERROR: The NIF must be a number!\n");
        goto NIFNUMBERLABEL;
      }
    }
    //transform NIF into integer
    sscanf(NIFtemp,"%"SCNu32,&NIF);
    //verify input
    if(strlen(NIFtemp)-1!=9){
      fprintf(stderr,"ERROR: The NIF must be a 9 digit number!\n");
      NIFNUMBERLABEL:
      strcpy(NIFtemp,"");
      continue;
    }
    else{
      return NIF;
    }
  }
}

void getName(char *name){
  char nameTemp[255];
  while(true){
    //header
    printf("            What is the name?            \n");
    //get name input
    if(fgets(nameTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the name!");
      }
      strcpy(nameTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      nameTemp[strcspn(nameTemp,"\n")]=0;
      strcpy(name,nameTemp);
      return;
    }
  }
}

void getAddress(char *address){
  char addressTemp[255];
  while(true){
    printf("           What's the address?           \n");
    //get address input
    if(fgets(addressTemp,255,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the address!");
      }
      strcpy(addressTemp,"");
      continue;
    }
    else{
      //remove newline and verify input
      addressTemp[strcspn(addressTemp,"\n")]=0;
      strcpy(address,addressTemp);
      return;
    }
  }
}

void getPhoneNumber(char *phoneNumber){
  char phoneTemp[100],country[100];
  while(true){
    printf("           What's the country?           \n");
    //get country input to check the phone code number
    if(fgets(country,100,stdin)==NULL){
      if(ferror(stdin)){
        perror("ERROR: There was an error reading the country!");
      }
      strcpy(phoneTemp,"");
      strcpy(country,"");
      strcpy(phoneNumber,"");
      continue;
    }
    else{
      //format country string
      country[strcspn(country,"\n")]=0;
      for(size_t i=0;i<strlen(country)-1;i++){
        country[i]=tolower(country[i]);
      }
      //check countries
      FILE *fileCountry=fopen("in/countries","r");
      if(fileCountry==NULL){
        perror("ERROR: There was an error checking the countries!");
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
          printf("        What is the phone number?        \n");
          //get phone number input
          if(fgets(phoneTemp,100,stdin)==NULL){
            if(ferror(stdin)){
              perror("ERROR: There was an error reading the phone number!");
            }
            strcpy(phoneTemp,"");
            strcpy(country,"");
            strcpy(phoneNumber,"");
            goto PHONE_ERROR_LABEL;
          }
          else{
            //check if phone number is a string
            for(size_t i=0;i<strlen(phoneTemp)-1;i++){
              if(!isdigit(phoneTemp[i])){
                fprintf(stderr,"ERROR: The Phone Number must be a number!\n");
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
        fprintf(stderr,"ERROR: The country is not correct!\n");
        PHONE_ERROR_LABEL:
        strcpy(phoneTemp,"");
        strcpy(country,"");
        strcpy(phoneNumber,"");
        continue;
      }
      return;
    }
  }
}

void printClient(CLIENT client){
  printf("===========================================\n");
  printf("             |> %s                \n",client.name);
  printf("                                     \n");
  printf("                 NIF: %"PRIu32"      \n",client.NIF);
  printf("             ADDRESS: %s             \n",client.address);
  printf("        PHONE NUMBER: %s             \n",client.phoneNumber);
  printf("        == PRESS ENTER TO EXIT ==    \n");
  printf("===========================================\n"); 
}