//global includes
#include<stdio.h>
#include<stdbool.h>
#include<inttypes.h>
#include<string.h>
//project includes
#include"clientOperations.h"
#include"client.h"

extern clientNODE *clientlist;

CLIENT newClient(void){
  bool correctInput[4]={false,false,false,false};
  uint32_t NIF;
  char name[255],address[255],phoneNumber[17];
  printf("=========================================\n");
  printf("      ========= NEW CLIENT =========     \n");
  while(!correctInput[0]||!correctInput[1]||!correctInput[2]||!correctInput[3]){
    if(!correctInput[0]){
      printf("             What's the NIF?             \n");
      if(scanf("%"SCNu32,&NIF)==EOF){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the NIF!");
        }
        NIF=-1;
      }
      if((NIF<100000000||NIF>999999999)||lsearchlinked(clientlist,NIF)){
        continue;
      }
      else{
        correctInput[0]=true;
      }
    }
    if(!correctInput[1]){
      printf("            What is the name?            \n");
      if(scanf("%s",name)==EOF){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the name!");
        }
        continue;
      }
      else{
        correctInput[1]=true;
      }
    }
    if(!correctInput[2]){
      printf("           What's the address?           \n");
      if(scanf("%s",address)==EOF){
        if(ferror(stdin)){
          perror("ERROR: There was an error reading the address!");
        }
        continue;
      }
      else{
        correctInput[2]=true;
        correctInput[3]=true;
      }
    }
  }
  CLIENT client;
  client.NIF=NIF;
  strcpy(client.name,name);
  strcpy(client.address,address);
  return client;
}