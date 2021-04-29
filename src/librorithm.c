//global includes
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<signal.h>
//project includes
#include"librorithm.h"
#include"handlers.h"
#include"menu.h"
#include"client.h"

extern clientNODE *clientlist;

int main(void){
  //handle signals
  if(signal(SIGINT,handleSignals)==SIG_ERR||signal(SIGQUIT,handleSignals)==SIG_ERR){
    fprintf(stderr,"|============================================================|\n");
    fprintf(stderr,"|  WARNING: Your system does not allow for signal handling!  |\n");
    fprintf(stderr,"|============================================================|\n");  
  }
  //handle exit
  if(atexit(printExitMessage)!=0){
    fprintf(stderr,"|===================================================================|\n");
    fprintf(stderr,"|  WARNING: Your system does not allow for setting exit functions!  |\n");
    fprintf(stderr,"|===================================================================|\n");
  }
  //menu
  mainMenu();
  //cleanup
  freelinked(clientlist);
  return 0;
}