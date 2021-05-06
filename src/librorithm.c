//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>
//project includes
#include"librorithm.h"
#include"handlers.h"
#include"menu.h"
#include"client.h"
#include"order.h"
//global variables
char prompt[100]="admin@";
extern clientNODE *clientlist;
extern ORDER_NODE_QUEUE *orderQueue;

int main(void){
  //setup prompt
  setupPrompt();
  //handle signals
  if(signal(SIGINT,handleSignals)==SIG_ERR||signal(SIGQUIT,handleSignals)==SIG_ERR){
    fprintf(stderr,"\t|============================================================|\n");
    fprintf(stderr,"\t|  WARNING: Your system does not allow for signal handling!  |\n");
    fprintf(stderr,"\t|============================================================|\n");  
  }
  //handle exit
  if(atexit(printExitMessage)!=0){
    fprintf(stderr,"\t|===================================================================|\n");
    fprintf(stderr,"\t|  WARNING: Your system does not allow for setting exit functions!  |\n");
    fprintf(stderr,"\t|===================================================================|\n");
  }
  //menu
  mainMenu();
  //cleanup
  cleanup();  
  return 0;
}

/**
 * Frees and cleans up memory to avoid memory leaks
 */
void cleanup(void){
  freelinked(clientlist);
  freequeue(&orderQueue); 
}

/**
 * Sets up the initial admin prompt
 */
void setupPrompt(void){
  struct utsname unameData;
  uname(&unameData);
  strcat(prompt,unameData.nodename);
  strcat(prompt,"# ");
}

/**
 * Prints the prompt
 */
void printPrompt(void){
  printf("%s",prompt);
}