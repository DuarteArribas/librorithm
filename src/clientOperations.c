//global includes
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
#include<ctype.h>
//project includes
#include"clientOperations.h"
#include"client.h"

extern clientNODE *clientlist;

static 
void printClientStart(void){
  printf("=========================================\n");
  printf("      ========= NEW CLIENT =========     \n");
}

CLIENT newClient(void){
  //handle wrong inputs
  bool correctInput[4]={false,false,false,false};
  //hold input info
  uint32_t NIF;
  char name[255],address[255],phoneNumber[17];
  //start heading
  printClientStart();
  //run untill all input are correct
  while(!correctInput[0]||!correctInput[1]||!correctInput[2]||!correctInput[3]){
    //NIF input
    if(!correctInput[0]){
      printf("             What's the NIF?             \n");
      char NIFtemp[100];
      if(fgets(NIFtemp,255,stdin)==NULL){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the NIF!");
        }
        continue;
      }
      for(size_t i=0;i<strlen(NIFtemp)-1;i++){
        if(!isdigit(NIFtemp[i])){
          fprintf(stderr,"ERROR: The NIF must be a number!\n");
          goto NIFNUMBERLABEL;
        }
      }
      sscanf(NIFtemp,"%"SCNu32,&NIF);
      if(strlen(NIFtemp)-1!=9||lsearchlinked(clientlist,NIF)){
        NIFNUMBERLABEL:
        continue;
      }
      else{
        correctInput[0]=true;
      }
    }
    //name input
    if(!correctInput[1]){
      printf("            What is the name?            \n");
      if(fgets(name,255,stdin)==NULL){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the name!");
        }
        continue;
      }
      else{
        name[strcspn(name,"\n")]=0;
        correctInput[1]=true;
      }
    }
    //address input
    if(!correctInput[2]){
      printf("           What's the address?           \n");
      if(fgets(address,255,stdin)==NULL){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the address!");
        }
        continue;
      }
      else{
        address[strcspn(address,"\n")]=0;
        correctInput[2]=true;
      }
    }
    //phone input
    if(!correctInput[3]){
      char country[100];
      printf("           What's the country?           \n");
      if(scanf("%s",country)==EOF){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the country!");
        }
        continue;
      }
      else{
        FILE *fileCountry=fopen("in/countries","r");
        if(fileCountry==NULL){
          perror("ERROR: There was an error checking the countries!");
          continue;
        }
        char temp[100],temp2[100];
        while(fscanf(fileCountry,"%s %s",temp,temp2)==2){
          if(strcmp(country,temp)==0){
            printf("        What is the phone number?        \n");
            char *plus="+";
            strcpy(phoneNumber,plus);
            strcat(phoneNumber,temp2);
            char phoneTemp[100];
            if(scanf("%s",phoneTemp)==EOF){
              if(ferror(stdin)){
                perror("ERROR: There was an error reading the phone number!");
              }
              goto phoneError;
            }
            else{
              strcat(phoneNumber,phoneTemp);
              goto phoneCorrect;
            }
          }
        }
        phoneError:
        continue;
        phoneCorrect:
        correctInput[3]=true;
      }
    }
  }
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